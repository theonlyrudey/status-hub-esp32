//
// Created by Piotr Rudnicki on 09/05/2026.
//

#pragma once

#include "StatusEvent.h"

class IStatusUpdater {
public:
    virtual ~IStatusUpdater() = default;
    virtual void setStatus(const StatusEvent& status) = 0;
};
