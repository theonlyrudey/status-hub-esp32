//
// Created by Piotr Rudnicki on 08/05/2026.
//

#include "WifiManager.h"

#include <algorithm>
#include <cstring>

namespace {
    bool hasSsid(const WifiCredentials& credentials) {
        return credentials.ssid[0] != '\0';
    }

    std::uint32_t initialReconnectDelay(const WifiConfig& config) {
        const std::uint32_t initial = config.reconnectInitialMs == 0 ? 1000U : config.reconnectInitialMs;
        if (config.reconnectMaxMs == 0) {
            return initial;
        }
        return std::min(initial, config.reconnectMaxMs);
    }

    template <std::size_t N>
    void copyStringToField(const char* source, char (&destination)[N]) {
        static_assert(N > 0, "Field size must be greater than 0");
        if (source == nullptr) {
            destination[0] = '\0';
            return;
        }
        std::strncpy(destination, source, N - 1);
        destination[N - 1] = '\0';
    }
} // namespace

WifiManager::WifiManager(IWifiAdapter &wifiAdapter, ICredentialsStore &credentialsStore, const WifiConfig &config) :
        _wifiAdapter(wifiAdapter), _credentialsStore(credentialsStore), _config(config) {
    _currentReconnectDelayMs = initialReconnectDelay(_config);
    _listeners.reserve(4);
}

void WifiManager::begin() {
    if (_credentialsStore.load(_currentCredentials) && hasSsid(_currentCredentials)) {
        _connectRequested = true;
        setState(WifiState::Disconnected, 0);
        return;
    }

    setState(WifiState::Idle, 0);
}

void WifiManager::tick(std::uint32_t nowMs) {
    if (_disconnectRequested) {
        _disconnectRequested = false;
        _connectRequested = false;
        _wifiAdapter.disconnect();
        setState(WifiState::Disconnected, nowMs);
        return;
    }

    if (_wifiAdapter.isConnected()) {
        if (_state != WifiState::Connected) {
            setState(WifiState::Connected, nowMs);
        }
        return;
    }

    if (_state == WifiState::Connected) {
        setState(WifiState::Disconnected, nowMs);
    }

    if (_connectRequested) {
        _connectRequested = false;
        tryStartConnect(nowMs);
        return;
    }

    if (_state == WifiState::Connecting) {
        if (_config.connectTimeoutMs > 0 && (nowMs - _stateSinceMs) >= _config.connectTimeoutMs) {
            _wifiAdapter.disconnect();
            setState(WifiState::Disconnected, nowMs);
        }
        return;
    }

    if (_state == WifiState::Disconnected && _config.autoReconnect) {
        handleReconnect(nowMs);
    }
}

void WifiManager::requestConnect() {
    _connectRequested = true;
}

void WifiManager::requestDisconnect() {
    _disconnectRequested = true;
}

bool WifiManager::updateCredentials(const WifiCredentials &credentials) {
    if (!hasSsid(credentials)) {
        return false;
    }

    _currentCredentials = credentials;
    _credentialsStore.save(credentials);

    _currentReconnectDelayMs = initialReconnectDelay(_config);
    _connectRequested = true;
    return true;
}

bool WifiManager::updateCredentials(const char *ssid, const char *password) {
    WifiCredentials credentials{};
    copyStringToField(ssid, credentials.ssid);
    copyStringToField(password, credentials.password);
    return updateCredentials(credentials);
}

WifiState WifiManager::state() const {
    return _state;
}

void WifiManager::addListener(IWifiStatusListener *listener) {
    if (listener == nullptr) {
        return;
    }

    if (std::find(_listeners.begin(), _listeners.end(), listener) != _listeners.end()) {
        return;
    }

    _listeners.push_back(listener);
    listener->onWifiStatusChanged(_state);
}

void WifiManager::removeListener(IWifiStatusListener *listener) {
    auto it = std::remove(_listeners.begin(), _listeners.end(), listener);
    _listeners.erase(it, _listeners.end());
}

void WifiManager::setState(const WifiState newState, const std::uint32_t nowMs) {
    if (_state == newState) {
        return;
    }

    _state = newState;
    _stateSinceMs = nowMs;

    if (_state == WifiState::Connected) {
        _currentReconnectDelayMs = initialReconnectDelay(_config);
    }

    for (auto* listener : _listeners) {
        if (listener != nullptr) {
            listener->onWifiStatusChanged(_state);
        }
    }
}

void WifiManager::tryStartConnect(const std::uint32_t nowMs) {
    if (!hasSsid(_currentCredentials)) {
        setState(WifiState::Error, nowMs);
        return;
    }

    _wifiAdapter.beginSta(_currentCredentials);
    _lastReconnectAttemptMs = nowMs;
    setState(WifiState::Connecting, nowMs);
}

void WifiManager::handleReconnect(const std::uint32_t nowMs) {
    if (!hasSsid(_currentCredentials)) {
        return;
    }

    if (_lastReconnectAttemptMs != 0 && (nowMs - _lastReconnectAttemptMs) < _currentReconnectDelayMs) {
        return;
    }

    tryStartConnect(nowMs);

    const std::uint32_t maxDelay = _config.reconnectMaxMs == 0
        ? _currentReconnectDelayMs
        : _config.reconnectMaxMs;

    const std::uint64_t doubled = static_cast<std::uint64_t>(_currentReconnectDelayMs) * 2ULL;
    _currentReconnectDelayMs = static_cast<std::uint32_t>(
        std::min<std::uint64_t>(doubled, maxDelay));
}
