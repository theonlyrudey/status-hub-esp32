//
// Created by Piotr Rudnicki on 08/05/2026.
//

#include "Network/Implementations/WifiStatusSerialListener.h"

using namespace statushub;

#include "Network/Interfaces/WifiTypes.h"

WifiStatusSerialListener::WifiStatusSerialListener(Print& serial) : _serial(serial) { }

void WifiStatusSerialListener::onWifiStatusChanged(const WifiStatusEvent& event) {
    _serial.print("WiFi status changed: ");
    switch (event.state) {
        case WifiState::Idle:
            _serial.println("Idle");
            break;
        case WifiState::Connecting:
            _serial.println("Connecting");
            break;
        case WifiState::Connected:
            _serial.print("Connected");
            if (event.hasLocalIp()) {
                _serial.print(" (");
                _serial.print(event.localIp);
                _serial.print(")");
            }
            _serial.println();
            break;
        case WifiState::Disconnected:
            _serial.println("Disconnected");
            break;
        case WifiState::Error:
            _serial.println("Error");
            break;
        case WifiState::Provisioning:
            _serial.println("Provisioning");
            break;
    }
}
