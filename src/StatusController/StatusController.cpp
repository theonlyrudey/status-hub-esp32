//
// Created by Piotr Rudnicki on 20/04/2026.
//

#include "StatusController.h"

void StatusController::addListener(IStatusListener *listener) {
    if (listener == nullptr) {
        return;
    }

    for (auto &l : _listeners) {
        if (l == listener) {
            return;
        }
    }

    _listeners.push_back(listener);
}

void StatusController::removeListener(IStatusListener *listener) {
    for (auto it = _listeners.begin(); it != _listeners.end(); ++it) {
        if (*it == listener) {
            _listeners.erase(it);
            return;
        }
    }
}

void StatusController::setStatus(const StatusEvent &status) {
    if (_currentStatus == status) {
        return;
    }
    _currentStatus = status;

    for (auto* l : _listeners) {
        if (l != nullptr) {
            l->onStatusChanged(status);
        }
    }
}

StatusEvent StatusController::getStatus() const {
    return _currentStatus;
}
