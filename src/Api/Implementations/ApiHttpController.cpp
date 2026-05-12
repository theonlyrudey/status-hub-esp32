//
// Created by Piotr Rudnicki on 09/05/2026.
//

#include "Api/Implementations/ApiHttpController.h"

using namespace statushub;

#include <ArduinoJson.h>

#include "StatusController/Implementations/StatusCodec.h"

namespace {
    template <typename TDoc>
    String serializeJsonResponse(TDoc& doc) {
        String output;
        serializeJson(doc, output);
        return output;
    }
}

ApiHttpController::ApiHttpController(IHttpServer& httpServer,
                                     IStatusUpdater& statusUpdater,
                                     const IStatusRequestParser& statusRequestParser)
    : _httpServer(httpServer),
      _statusUpdater(statusUpdater),
      _statusRequestParser(statusRequestParser) {}

void ApiHttpController::begin() {
    if (_routeRegistered) {
        return;
    }

    _httpServer.onPost("/status", [this]() { handleSetStatusRequest(); });
    _routeRegistered = true;
}

void ApiHttpController::tick(const std::uint32_t nowMs) {
    _lastTickMs = nowMs;
    if (!_serverStarted) {
        return;
    }
    _httpServer.handleClient();
}

void ApiHttpController::onWifiStatusChanged(const WifiStatusEvent& event) {
    if (event.state == WifiState::Connected) {
        if (!_routeRegistered) {
            begin();
        }

        if (_serverStarted) {
            return;
        }

        _httpServer.begin();
        _serverStarted = true;
        return;
    }

    if (!_serverStarted) {
        return;
    }

    _httpServer.stop();
    _serverStarted = false;
}

void ApiHttpController::handleSetStatusRequest() {
    String requestBody;
    if (!_httpServer.tryGetRequestBody(requestBody)) {
        sendErrorResponse(400, "Request body must contain JSON.");
        return;
    }

    StatusEvent statusEvent{};
    String parseError;
    if (!_statusRequestParser.tryParseStatusRequest(requestBody, _lastTickMs, statusEvent, parseError)) {
        sendErrorResponse(400, parseError);
        return;
    }

    _statusUpdater.setStatus(statusEvent);
    sendSuccessResponse(statusEvent);
}

void ApiHttpController::sendErrorResponse(const int statusCode, const String& message) {
    JsonDocument doc;
    doc["ok"] = false;
    doc["error"] = message;
    _httpServer.send(statusCode, "application/json", serializeJsonResponse(doc));
}

void ApiHttpController::sendSuccessResponse(const StatusEvent& statusEvent) {
    JsonDocument doc;
    doc["ok"] = true;
    doc["status"] = StatusCodec::toString(statusEvent.status);
    doc["receivedAtMs"] = statusEvent.receivedAtMs;
    doc["source"] = statusEvent.source;
    if (statusEvent.message[0] != '\0') {
        doc["message"] = statusEvent.message;
    }
    _httpServer.send(200, "application/json", serializeJsonResponse(doc));
}
