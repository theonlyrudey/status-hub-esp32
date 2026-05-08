//
// Created by Piotr Rudnicki on 08/05/2026.
//

#pragma once
#include <cstdint>
#include <cstring>

enum class WifiState {
    Idle,
    Connecting,
    Connected,
    Disconnected,
    Provisioning,
    Error
};

struct WifiCredentials {
    char ssid[32];
    char password[64];
};

inline WifiCredentials makeWifiCredentials(const char* ssid, const char* password) {
    WifiCredentials credentials{};
    if (ssid != nullptr) {
        std::strncpy(credentials.ssid, ssid, sizeof(credentials.ssid) - 1);
        credentials.ssid[sizeof(credentials.ssid) - 1] = '\0';
    }
    if (password != nullptr) {
        std::strncpy(credentials.password, password, sizeof(credentials.password) - 1);
        credentials.password[sizeof(credentials.password) - 1] = '\0';
    }
    return credentials;
}

struct WifiConfig {
    std::uint32_t connectTimeoutMs = 15000;
    std::uint32_t reconnectInitialMs = 2000;
    std::uint32_t reconnectMaxMs = 60000;
    bool autoReconnect = true;
};
