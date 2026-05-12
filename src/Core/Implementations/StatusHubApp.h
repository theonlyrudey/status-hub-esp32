//
// Created by Piotr Rudnicki on 08/05/2026.
//

#pragma once

#include <optional>
#include <MD_MAX72xx.h>

#include "Api/Implementations/ApiHttpController.h"
#include "Api/Implementations/ArduinoWebServerAdapter.h"
#include "Api/Implementations/StatusRequestParser.h"
#include "Core/Implementations/AppRuntime.h"
#include "Display/Implementations/Animation/AnimationController.h"
#include "Display/Implementations/MatrixStatusListener.h"
#include "Display/Implementations/MatrixDisplayBackend.h"
#include "Display/Implementations/OledStatusDisplayBackend.h"
#include "Display/Implementations/OledStatusListener.h"
#include "Input/Implementations/IdleButtonService.h"
#include "Network/Implementations/Esp32WifiAdapter.h"
#include "Network/Implementations/MdnsService.h"
#include "Network/Implementations/PreferencesCredentialsStore.h"
#include "Network/Implementations/WifiManager.h"
#include "Network/Implementations/WifiStatusSerialListener.h"
#include "StatusController/Implementations/StatusController.h"

namespace statushub {

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
    AnimationController _matrixAnimationController;
    MatrixStatusListener _matrixDisplayStatusListener;
    OledStatusDisplayBackend _oledStatusDisplayBackend;
    AnimationController _oledDisplayAnimationController;
    OledStatusListener _oledStatusListener;
    IdleButtonService _idleButtonService;
    Esp32WifiAdapter _wifiAdapter;
    PreferencesCredentialsStore _credentialsStore;
    WifiManager _wifiManager;
    std::optional<WifiStatusSerialListener> _wifiStatusSerialListener;
};

} // namespace statushub
