//
// Created by Piotr Rudnicki on 09/05/2026.
//

#include "Api/Implementations/ArduinoWebServerAdapter.h"

using namespace statushub;

#include <HTTP_Method.h>
#include <utility>

ArduinoWebServerAdapter::ArduinoWebServerAdapter(const int port) : _server(port) {}

void ArduinoWebServerAdapter::onPost(const char* path, RequestHandler handler) {
    _server.on(path, HTTP_POST, std::move(handler));
}

void ArduinoWebServerAdapter::begin() {
    _server.begin();
}

void ArduinoWebServerAdapter::stop() {
    _server.stop();
}

void ArduinoWebServerAdapter::handleClient() {
    _server.handleClient();
}

bool ArduinoWebServerAdapter::tryGetRequestBody(String& outBody) {
    if (!_server.hasArg("plain")) {
        return false;
    }

    outBody = _server.arg("plain");
    return true;
}

void ArduinoWebServerAdapter::send(const int statusCode, const char* contentType, const String& payload) {
    _server.send(statusCode, contentType, payload);
}
