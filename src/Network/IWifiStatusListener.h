//
// Created by Piotr Rudnicki on 08/05/2026.
//

#ifndef AGENTNOTIFICATOR_IWIFISTATUSLISTENER_H
#define AGENTNOTIFICATOR_IWIFISTATUSLISTENER_H

enum class WifiState;

class IWifiStatusListener {
public:
    virtual ~IWifiStatusListener() = default;
    virtual void onWifiStatusChanged(WifiState state) = 0;
};
#endif //AGENTNOTIFICATOR_IWIFISTATUSLISTENER_H
