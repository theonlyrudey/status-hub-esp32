//
// Created by Piotr Rudnicki on 09/05/2026.
//

#pragma once

#include <WString.h>
#include <cstdint>

#include "StatusController/Implementations/StatusEvent.h"

namespace statushub {

class IStatusRequestParser {
public:
    virtual ~IStatusRequestParser() = default;
    virtual bool tryParseStatusRequest(const String& requestBody,
                                       std::uint32_t nowMs,
                                       StatusEvent& outStatusEvent,
                                       String& outErrorMessage) const = 0;
};

} // namespace statushub
