//
// Created by Piotr Rudnicki on 08/05/2026.
//

#pragma once
#include <WString.h>

namespace statushub {

struct WifiCredentials;

class IWifiAdapter {
public:
    virtual ~IWifiAdapter() = default;
    virtual void beginSta(const WifiCredentials& credentials) = 0;
    virtual void disconnect() = 0;
    virtual void reconnect() = 0;
    virtual bool isConnected() = 0;
    virtual String localIP() = 0;
};

} // namespace statushub
