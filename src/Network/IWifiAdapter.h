//
// Created by Piotr Rudnicki on 08/05/2026.
//

#ifndef AGENTNOTIFICATOR_IWIFIADAPTER_H
#define AGENTNOTIFICATOR_IWIFIADAPTER_H
#include <WString.h>

struct WifiCredentials;

class IWifiAdapter {
public:
    virtual ~IWifiAdapter() = default;
    virtual void beginSta(const WifiCredentials& credentials) = 0;
    virtual void disconnect() = 0;
    virtual void reconnect() = 0;
    virtual bool isConnected() const = 0;
    virtual String localIP() const = 0;
};
#endif //AGENTNOTIFICATOR_IWIFIADAPTER_H
