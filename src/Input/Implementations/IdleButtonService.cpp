//
// Created by Piotr Rudnicki on 11/05/2026.
//

#include "Input/Implementations/IdleButtonService.h"

using namespace statushub;

#include <Arduino.h>

#include "StatusController/Implementations/Status.h"
#include "StatusController/Implementations/StatusEvent.h"

IdleButtonService::IdleButtonService(IStatusUpdater &statusUpdater,
                                     const std::uint8_t buttonPin,
                                     const bool activeLow,
                                     const std::uint32_t debounceMs) :
    _statusUpdater(statusUpdater),
    _buttonPin(buttonPin),
    _activeLow(activeLow),
    _debounceMs(debounceMs) {}

void IdleButtonService::begin() {
    pinMode(_buttonPin, _activeLow ? INPUT_PULLUP : INPUT_PULLDOWN);

    const bool pressed = readPressed();
    _lastSamplePressed = pressed;
    _hasAcceptedPress = false;
    _lastAcceptedPressMs = 0;
    _initialized = true;
}

void IdleButtonService::tick(const std::uint32_t nowMs) {
    if (!_initialized) {
        return;
    }

    const bool samplePressed = readPressed();
    if (samplePressed == _lastSamplePressed) {
        return;
    }

    _lastSamplePressed = samplePressed;

    if (!samplePressed) {
        return;
    }

    if (_hasAcceptedPress && (nowMs - _lastAcceptedPressMs) < _debounceMs) {
        return;
    }

    _hasAcceptedPress = true;
    _lastAcceptedPressMs = nowMs;
    _statusUpdater.setStatus(StatusEvent{Status::Idle, nowMs, "button"});
}

bool IdleButtonService::readPressed() const {
    const int level = digitalRead(_buttonPin);
    return _activeLow ? level == LOW : level == HIGH;
}
