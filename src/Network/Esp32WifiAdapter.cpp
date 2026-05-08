//
// Created by Piotr Rudnicki on 08/05/2026.
//

#include "Esp32WifiAdapter.h"
#include "Network/WifiTypes.h"

void Esp32WifiAdapter::beginSta(const WifiCredentials &credentials) {
    _wifi.mode(WIFI_STA);
    _wifi.begin(credentials.ssid, credentials.password);
}

void Esp32WifiAdapter::disconnect() {
    _wifi.disconnect();
}

void Esp32WifiAdapter::reconnect() {
    _wifi.reconnect();
}

bool Esp32WifiAdapter::isConnected() {
    return _wifi.status() == WL_CONNECTED;
}

String Esp32WifiAdapter::localIP() {
    if (!_wifi.isConnected()) {
        return String();
    }
    return _wifi.localIP().toString();
}