//
// Created by Piotr Rudnicki on 08/05/2026.
//

#include "Core/Implementations/StatusHubApp.h"

using namespace statushub;

#include <Arduino.h>
#include <cstdint>

#include "secrets.h"

namespace {
    constexpr auto HARDWARE_TYPE = MD_MAX72XX::GENERIC_HW;
    constexpr std::uint8_t MAX_DEVICES = 1;
    constexpr std::uint8_t CS_PIN = 5;
    constexpr std::uint8_t OLED_SDA_PIN = 33;
    constexpr std::uint8_t OLED_SCL_PIN = 32;
    constexpr std::uint8_t OLED_I2C_ADDRESS = 0x3C;
    constexpr std::uint8_t IDLE_BUTTON_PIN = 21;
    constexpr bool IDLE_BUTTON_ACTIVE_LOW = true;
    constexpr std::uint32_t IDLE_BUTTON_DEBOUNCE_MS = 25U;
}

StatusHubApp::StatusHubApp() :
    _matrix(HARDWARE_TYPE, CS_PIN, MAX_DEVICES),
    _httpServer(80),
    _statusRequestParser("http-api"),
    _apiHttpController(_httpServer, _statusController, _statusRequestParser),
    _matrixDisplayBackend(_matrix),
    _matrixAnimationController(_matrixDisplayBackend),
    _matrixDisplayStatusListener(_matrixAnimationController),
    _oledStatusDisplayBackend(Wire, OLED_SDA_PIN, OLED_SCL_PIN, OLED_I2C_ADDRESS),
    _oledDisplayAnimationController(_oledStatusDisplayBackend),
    _oledStatusListener(_oledDisplayAnimationController),
    _idleButtonService(_statusController, IDLE_BUTTON_PIN, IDLE_BUTTON_ACTIVE_LOW, IDLE_BUTTON_DEBOUNCE_MS),
    _wifiManager(_wifiAdapter, _credentialsStore, _wifiConfig) {}

void StatusHubApp::begin() {
    Serial.begin(115200);
    _matrixDisplayBackend.init();
    _oledStatusDisplayBackend.init();

    _matrixDisplayStatusListener.setAnimationMode(AnimationMode::Sequence, false);
    _idleButtonService.begin();

    _wifiStatusSerialListener.emplace(Serial);
    _wifiManager.addListener(&_wifiStatusSerialListener.value());
    _wifiManager.addListener(&_apiHttpController);
    _wifiManager.addListener(&_mdnsService);
    _wifiManager.updateCredentials(WIFI_SSID, WIFI_PASSWORD);
    _wifiManager.begin();
    _apiHttpController.begin();

    _statusController.addListener(&_matrixDisplayStatusListener);
    _statusController.addListener(&_oledStatusListener);
    _appRuntime.registerTickable(&_matrixAnimationController);
    _appRuntime.registerTickable(&_oledDisplayAnimationController);
    _appRuntime.registerTickable(&_idleButtonService);
    _appRuntime.registerTickable(&_wifiManager);
    _appRuntime.registerTickable(&_apiHttpController);
    _statusController.setStatus(StatusEvent(Status::Idle, millis(), "setup"));
}

void StatusHubApp::loop() const {
    _appRuntime.loop();
}
