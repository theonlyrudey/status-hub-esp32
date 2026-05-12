//
// Created by Piotr Rudnicki on 20/04/2026.
//

#pragma once
#include "StatusController/Implementations/StatusEvent.h"

namespace statushub {

class IStatusListener {
public:
    virtual ~IStatusListener() = default;
    virtual void onStatusChanged(StatusEvent newStatus) = 0;
};

} // namespace statushub
