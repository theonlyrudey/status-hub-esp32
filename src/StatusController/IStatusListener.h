//
// Created by Piotr Rudnicki on 20/04/2026.
//

#pragma once
#include "StatusEvent.h"

class IStatusListener {
public:
    virtual ~IStatusListener() = default;
    virtual void onStatusChanged(StatusEvent newStatus) = 0;
};
