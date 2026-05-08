//
// Created by Piotr Rudnicki on 08/05/2026.
//

#ifndef AGENTNOTIFICATOR_WIFITYPES_H
#define AGENTNOTIFICATOR_WIFITYPES_H
#include <cstdint>

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

struct WifiConfig {
    std::uint32_t connectTimeoutMs = 15000;
    std::uint32_t reconnectInitialMs = 2000;
    std::uint32_t reconnectMaxMs = 60000;
    bool autoReconnect = true;
};
#endif //AGENTNOTIFICATOR_WIFITYPES_H
