//
// Created by Piotr Rudnicki on 09/05/2026.
//

#pragma once

#include <cstdint>

#include "Core/ITickable.h"
#include "IHttpServer.h"
#include "IStatusRequestParser.h"
#include "Network/IWifiStatusListener.h"
#include "StatusController/IStatusUpdater.h"

class ApiHttpController : public ITickable, public IWifiStatusListener {
public:
    ApiHttpController(IHttpServer& httpServer,
                      IStatusUpdater& statusUpdater,
                      const IStatusRequestParser& statusRequestParser);

    void begin();
    void tick(std::uint32_t nowMs) override;
    void onWifiStatusChanged(const WifiStatusEvent& event) override;

private:
    void handleSetStatusRequest();
    void sendErrorResponse(int statusCode, const String& message);
    void sendSuccessResponse(const StatusEvent& statusEvent);

    IHttpServer& _httpServer;
    IStatusUpdater& _statusUpdater;
    const IStatusRequestParser& _statusRequestParser;
    std::uint32_t _lastTickMs = 0;
    bool _routeRegistered = false;
    bool _serverStarted = false;
};
