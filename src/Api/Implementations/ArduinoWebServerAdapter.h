//
// Created by Piotr Rudnicki on 09/05/2026.
//

#pragma once

#include <WebServer.h>

#include "Api/Interfaces/IHttpServer.h"

namespace statushub {

class ArduinoWebServerAdapter final : public IHttpServer {
public:
    explicit ArduinoWebServerAdapter(int port = 80);

    void onPost(const char* path, RequestHandler handler) override;
    void begin() override;
    void stop() override;
    void handleClient() override;
    bool tryGetRequestBody(String& outBody) override;
    void send(int statusCode, const char* contentType, const String& payload) override;

private:
    WebServer _server;
};

} // namespace statushub
