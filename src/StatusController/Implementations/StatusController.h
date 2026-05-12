//
// Created by Piotr Rudnicki on 20/04/2026.
//

#pragma once

#include <vector>

#include "StatusController/Interfaces/IStatusListener.h"
#include "StatusController/Interfaces/IStatusUpdater.h"
#include "StatusController/Implementations/Status.h"

namespace statushub {

class StatusController : public IStatusUpdater {
public:
    void addListener(IStatusListener *listener);
    void removeListener(IStatusListener *listener);
    void setStatus(const StatusEvent &status) override;

    StatusEvent getStatus() const;

private:
    StatusEvent _currentStatus{Status::Invalid, 0, "in-app"};
    std::vector<IStatusListener*> _listeners;
};


} // namespace statushub
