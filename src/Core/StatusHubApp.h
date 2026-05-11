//
// Created by Piotr Rudnicki on 08/05/2026.
//

#pragma once

#include <optional>
#include <MD_MAX72xx.h>

#include "Api/ApiHttpController.h"
#include "Api/ArduinoWebServerAdapter.h"
#include "Api/StatusRequestParser.h"
#include "AppRuntime.h"
#include "Display/Animation/AnimationController.h"
#include "Display/DisplayStatusListener.h"
#include "Display/MatrixDisplayBackend.h"
#include "Input/IdleButtonService.h"
#include "Network/Esp32WifiAdapter.h"
#include "Network/MdnsService.h"
#include "Network/PreferencesCredentialsStore.h"
#include "Network/WifiManager.h"
#include "Network/WifiStatusSerialListener.h"
#include "StatusController/StatusController.h"

class StatusHubApp {
public:
    StatusHubApp();
    void begin();
    void loop() const;

private:
    MD_MAX72XX _matrix;
    WifiConfig _wifiConfig{};
    StatusController _statusController{};
    ArduinoWebServerAdapter _httpServer;
    MdnsService _mdnsService{"status-hub"};
    StatusRequestParser _statusRequestParser;
    ApiHttpController _apiHttpController;
    AppRuntime _appRuntime{};

    MatrixDisplayBackend _matrixDisplayBackend;
    AnimationController _animationController;
    DisplayStatusListener _displayStatusListener;
    IdleButtonService _idleButtonService;
    Esp32WifiAdapter _wifiAdapter;
    PreferencesCredentialsStore _credentialsStore;
    WifiManager _wifiManager;
    std::optional<WifiStatusSerialListener> _wifiStatusSerialListener;
};
