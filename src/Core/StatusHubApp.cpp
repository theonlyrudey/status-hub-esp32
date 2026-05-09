//
// Created by Piotr Rudnicki on 08/05/2026.
//

#include "StatusHubApp.h"

#include <Arduino.h>
#include <cstdint>

#include "secrets.h"

namespace {
    constexpr auto HARDWARE_TYPE = MD_MAX72XX::GENERIC_HW;
    constexpr std::uint8_t MAX_DEVICES = 1;
    constexpr std::uint8_t CS_PIN = 5;
}

StatusHubApp::StatusHubApp() :
    _matrix(HARDWARE_TYPE, CS_PIN, MAX_DEVICES),
    _matrixDisplayBackend(_matrix),
    _animationController(_matrixDisplayBackend),
    _displayStatusListener(_animationController),
    _wifiManager(_wifiAdapter, _credentialsStore, _wifiConfig) {}

void StatusHubApp::begin() {
    Serial.begin(115200);
    _matrixDisplayBackend.init();
    _displayStatusListener.setAnimationMode(AnimationMode::ScrollBitmap, false);

    _wifiStatusSerialListener.emplace(Serial);
    _wifiManager.addListener(&_wifiStatusSerialListener.value());
    _wifiManager.updateCredentials(WIFI_SSID, WIFI_PASSWORD);
    _wifiManager.begin();

    _statusController.addListener(&_displayStatusListener);
    _appRuntime.registerTickable(&_animationController);
    _appRuntime.registerTickable(&_wifiManager);
    _statusController.setStatus(StatusEvent(Status::Idle, millis(), "setup"));
}

void StatusHubApp::loop() const {
    _appRuntime.loop();
}
