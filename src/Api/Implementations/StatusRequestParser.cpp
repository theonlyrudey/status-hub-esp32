//
// Created by Piotr Rudnicki on 09/05/2026.
//

#include "Api/Implementations/StatusRequestParser.h"

using namespace statushub;

#include <ArduinoJson.h>
#include <cstring>

#include "StatusController/Implementations/StatusCodec.h"

namespace {
    constexpr std::size_t MAX_SOURCE_LENGTH = 32;
    constexpr std::size_t MAX_MESSAGE_LENGTH = 96;
}

StatusRequestParser::StatusRequestParser(const char* defaultSource) : _defaultSource(defaultSource) {}

bool StatusRequestParser::tryParseStatusRequest(const String& requestBody,
                                                const std::uint32_t nowMs,
                                                StatusEvent& outStatusEvent,
                                                String& outErrorMessage) const {
    if (requestBody.length() == 0) {
        outErrorMessage = "Request body must not be empty.";
        return false;
    }

    JsonDocument doc;

    const DeserializationError err = deserializeJson(doc, requestBody);
    if (err) {
        outErrorMessage = "Request body is not valid JSON.";
        return false;
    }

    const JsonVariant statusVariant = doc["status"];
    if (!statusVariant.is<const char*>()) {
        outErrorMessage = "Field 'status' is required and must be a string.";
        return false;
    }

    Status parsedStatus = Status::Invalid;
    if (!StatusCodec::tryParseStatus(statusVariant.as<String>(), parsedStatus)) {
        outErrorMessage = "Field 'status' has unsupported value.";
        return false;
    }

    const JsonVariant metaVariant = doc["meta"];
    const char* source = _defaultSource;
    const char* message = "";
    if (!metaVariant.isNull()) {
        if (!metaVariant.is<JsonObject>()) {
            outErrorMessage = "Field 'meta' must be an object.";
            return false;
        }

        const JsonVariant sourceVariant = metaVariant["source"];
        if (!sourceVariant.isNull()) {
            if (!sourceVariant.is<const char*>()) {
                outErrorMessage = "Field 'meta.source' must be a string.";
                return false;
            }

            const char* providedSource = sourceVariant.as<const char*>();
            if (providedSource != nullptr && std::strlen(providedSource) >= MAX_SOURCE_LENGTH) {
                outErrorMessage = "Field 'meta.source' is too long.";
                return false;
            }
            source = providedSource;
        }

        const JsonVariant messageVariant = metaVariant["message"];
        if (!messageVariant.isNull()) {
            if (!messageVariant.is<const char*>()) {
                outErrorMessage = "Field 'meta.message' must be a string.";
                return false;
            }

            const char* providedMessage = messageVariant.as<const char*>();
            if (providedMessage != nullptr && std::strlen(providedMessage) >= MAX_MESSAGE_LENGTH) {
                outErrorMessage = "Field 'meta.message' is too long.";
                return false;
            }
            message = providedMessage;
        }
    }

    outStatusEvent = StatusEvent(parsedStatus, nowMs, source, message);
    return true;
}
