//
// Created by Piotr Rudnicki on 09/05/2026.
//

#include "StatusRequestParser.h"

#include <ArduinoJson.h>
#include <cstring>

#include "StatusController/StatusCodec.h"

namespace {
    constexpr std::size_t MAX_SOURCE_LENGTH = 32;
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
    }

    outStatusEvent = StatusEvent(parsedStatus, nowMs, source);
    return true;
}
