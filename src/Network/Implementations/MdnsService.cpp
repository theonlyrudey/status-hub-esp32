//
// Created by Piotr Rudnicki on 11/05/2026.
//

#include "Network/Implementations/MdnsService.h"

using namespace statushub;

MdnsService::MdnsService(const String &hostname) : _hostname(hostname) {}

void MdnsService::onWifiStatusChanged(const WifiStatusEvent &event) {
    if (event.state == WifiState::Connected) {
        begin();
    } else {
        stop();
    }
}

void MdnsService::begin() {
    if (_isRunning) {
        return;
    }

    if (!_mdnsResponder.begin(_hostname)) {
        return;
    }

    _mdnsResponder.addService("http", "tcp", 80);
    _isRunning = true;
}

void MdnsService::stop() {
    if (!_isRunning) {
        return;
    }

    _mdnsResponder.end();
    _isRunning = false;
}
