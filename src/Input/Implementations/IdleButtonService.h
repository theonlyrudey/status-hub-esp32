//
// Created by Piotr Rudnicki on 11/05/2026.
//

#pragma once

#include <cstdint>

#include "Core/Interfaces/ITickable.h"
#include "StatusController/Interfaces/IStatusUpdater.h"

namespace statushub {

class IdleButtonService : public ITickable {
public:
    IdleButtonService(IStatusUpdater& statusUpdater,
                      std::uint8_t buttonPin,
                      bool activeLow = true,
                      std::uint32_t debounceMs = 25U);

    void begin();
    void tick(std::uint32_t nowMs) override;

private:
    bool readPressed() const;

    IStatusUpdater& _statusUpdater;
    std::uint8_t _buttonPin;
    bool _activeLow;
    std::uint32_t _debounceMs;
    bool _initialized = false;
    bool _lastSamplePressed = false;
    bool _hasAcceptedPress = false;
    std::uint32_t _lastAcceptedPressMs = 0;
};

} // namespace statushub
