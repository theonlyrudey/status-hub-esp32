//
// Created by Piotr Rudnicki on 20/04/2026.
//

#pragma once

#include <vector>

#include "IStatusListener.h"
#include "IStatusUpdater.h"
#include "Status.h"

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

