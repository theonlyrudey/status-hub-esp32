//
// Created by Piotr Rudnicki on 09/05/2026.
//

#pragma once

#include <WString.h>
#include <functional>

class IHttpServer {
public:
    using RequestHandler = std::function<void()>;

    virtual ~IHttpServer() = default;
    virtual void onPost(const char* path, RequestHandler handler) = 0;
    virtual void begin() = 0;
    virtual void stop() = 0;
    virtual void handleClient() = 0;
    virtual bool tryGetRequestBody(String& outBody) = 0;
    virtual void send(int statusCode, const char* contentType, const String& payload) = 0;
};
