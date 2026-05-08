//
// Created by Piotr Rudnicki on 08/05/2026.
//

#pragma once

#include "IWifiAdapter.h"
#include <WiFi.h>

class Esp32WifiAdapter : public IWifiAdapter {
public:
    void beginSta(const WifiCredentials& credentials) override;
    void disconnect() override;
    void reconnect() override;
    bool isConnected() override;
    String localIP() override;

private:
    WiFiClass _wifi;
};
