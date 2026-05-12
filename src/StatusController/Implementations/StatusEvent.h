//
// Created by Piotr Rudnicki on 06/05/2026.
//

#pragma once

#include <cstdint>
#include <cstring>

#include "StatusController/Implementations/Status.h"

namespace statushub {

struct StatusEvent {
    Status status;
    std::uint32_t receivedAtMs = 0;
    char source[32] = "";
    char message[96] = "";

    bool operator==(const StatusEvent& other) const {
        return status == other.status &&
               receivedAtMs == other.receivedAtMs &&
               std::strcmp(source, other.source) == 0 &&
               std::strcmp(message, other.message) == 0;
    }

    bool operator!=(const StatusEvent& other) const {
        return !(*this == other);
    }

    explicit StatusEvent(Status s = Status::Invalid, std::uint32_t ms = 0, const char* src = "", const char* msg = "")
    : status(s), receivedAtMs(ms), source{}, message{} {
        std::strncpy(source, src, sizeof(source) - 1);
        std::strncpy(message, msg, sizeof(message) - 1);
    }
};

} // namespace statushub
