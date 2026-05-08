//
// Created by Piotr Rudnicki on 06/05/2026.
//

#include "StatusCodec.h"

namespace {
    struct StatusMapEntry {
        const char* name;
        Status status;
    };

    constexpr StatusMapEntry kStatusMap[] = {
        {"idle", Status::Idle},
        {"working", Status::Working},
        {"finished", Status::Finished},
        {"error", Status::Error},
    };
}

bool StatusCodec::tryParseStatus(const String& status, Status& outStatus) {
    String normalized = status;
    normalized.trim();
    normalized.toLowerCase();

    for (const auto& entry : kStatusMap) {
        if (normalized == entry.name) {
            outStatus = entry.status;
            return true;
        }
    }

    return false;
}

const char * StatusCodec::toString(const Status status) {
    for (const auto& entry : kStatusMap) {
        if (entry.status == status) {
            return entry.name;
        }
    }

    return "invalid";
}
