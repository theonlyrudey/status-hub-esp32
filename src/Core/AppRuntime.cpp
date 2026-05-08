//
// Created by Piotr Rudnicki on 06/05/2026.
//

#include "AppRuntime.h"

#include <algorithm>
#include <esp32-hal.h>

void AppRuntime::registerTickable(ITickable* tickable) {
    if (tickable == nullptr) {
        return;
    }

    for (auto &l : _tickables) {
        if (l == tickable) {
            return;
        }
    }

    _tickables.push_back(tickable);
}

void AppRuntime::unregisterTickable(ITickable* tickable) {
    for (auto it = _tickables.begin(); it != _tickables.end(); ++it) {
        if (*it == tickable) {
            _tickables.erase(it);
            return;
        }
    }
}

void AppRuntime::loop() const {
    for (auto* tickable : _tickables) {
        tickable->tick(millis());
    }
}
