//
// Created by Piotr Rudnicki on 08/05/2026.
//

#pragma once

#include "ICredentialsStore.h"
#include "IWifiAdapter.h"
#include "IWifiStatusListener.h"
#include "WifiTypes.h"
#include "Core/ITickable.h"

class WifiManager : public ITickable {
public:
    explicit WifiManager(IWifiAdapter& wifiAdapter, ICredentialsStore& credentialsStore, WifiConfig config);

    void tick(uint32_t nowMs) override;
    void begin();
    void requestConnect();
    void requestDisconnect();
    bool updateCredentials(const WifiCredentials& credentials);
    WifiState state() const;
    void addListener(IWifiStatusListener* listener);
    void removeListener(IWifiStatusListener* listener);
};


