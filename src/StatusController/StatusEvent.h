//
// Created by Piotr Rudnicki on 06/05/2026.
//

#pragma once

#include <cstdint>
#include <cstring>

#include "Status.h"

struct StatusEvent {
    Status status;
    std::uint32_t receivedAtMs = 0;
    char source[32] = "";

    bool operator==(const StatusEvent& other) const {
        return status == other.status && receivedAtMs == other.receivedAtMs && std::strcmp(source, other.source) == 0;
    }

    bool operator!=(const StatusEvent& other) const {
        return !(*this == other);
    }

    explicit StatusEvent(Status s = Status::Invalid, std::uint32_t ms = 0, const char* src = "")
    : status(s), receivedAtMs(ms), source{} {
        std::strncpy(source, src, sizeof(source) - 1);
    }
};
