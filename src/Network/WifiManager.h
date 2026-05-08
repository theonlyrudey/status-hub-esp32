//
// Created by Piotr Rudnicki on 08/05/2026.
//

#pragma once

#include <cstdint>
#include <vector>

#include "ICredentialsStore.h"
#include "IWifiAdapter.h"
#include "IWifiStatusListener.h"
#include "WifiTypes.h"
#include "Core/ITickable.h"

class WifiManager : public ITickable {
public:
    explicit WifiManager(IWifiAdapter& wifiAdapter, ICredentialsStore& credentialsStore, const WifiConfig &config);

    void tick(std::uint32_t nowMs) override;
    void begin();
    void requestConnect();
    void requestDisconnect();
    bool updateCredentials(const WifiCredentials& credentials);
    bool updateCredentials(const char* ssid, const char* password);
    WifiState state() const;
    void addListener(IWifiStatusListener* listener);
    void removeListener(IWifiStatusListener* listener);

private:
    void setState(WifiState newState, std::uint32_t nowMs);
    void tryStartConnect(std::uint32_t nowMs);
    void handleReconnect(std::uint32_t nowMs);

    IWifiAdapter& _wifiAdapter;
    ICredentialsStore& _credentialsStore;
    WifiConfig _config;
    WifiState _state {WifiState::Disconnected};
    WifiCredentials _currentCredentials{};

    bool _connectRequested = false;
    bool _disconnectRequested = false;

    std::uint32_t _stateSinceMs = 0;
    std::uint32_t _lastReconnectAttemptMs = 0;
    std::uint32_t _currentReconnectDelayMs = 0;

    std::vector<IWifiStatusListener*> _listeners;
};
