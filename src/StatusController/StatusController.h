//
// Created by Piotr Rudnicki on 20/04/2026.
//

#pragma once

#include <vector>

#include "IStatusListener.h"
#include "Status.h"

class StatusController {
public:
    void addListener(IStatusListener *listener);
    void removeListener(IStatusListener *listener);
    void setStatus(const StatusEvent &status);

    StatusEvent getStatus() const;

private:
    StatusEvent _currentStatus{Status::Invalid, 0, "in-app"};
    std::vector<IStatusListener*> _listeners;
};


