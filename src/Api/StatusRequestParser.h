//
// Created by Piotr Rudnicki on 09/05/2026.
//

#pragma once

#include "IStatusRequestParser.h"

class StatusRequestParser final : public IStatusRequestParser {
public:
    explicit StatusRequestParser(const char* defaultSource = "http-api");

    bool tryParseStatusRequest(const String& requestBody,
                               std::uint32_t nowMs,
                               StatusEvent& outStatusEvent,
                               String& outErrorMessage) const override;

private:
    const char* _defaultSource;
};
