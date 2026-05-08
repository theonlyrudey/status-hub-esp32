//
// Created by Piotr Rudnicki on 07/05/2026.
//

#pragma once
#include <cstdint>

struct ScrollState {
    const std::uint8_t* sourceBitmap{nullptr};
    std::uint32_t stepMs {250U};
    std::int8_t direction {1}; // +1 right, -1 left
    bool wrap{true};
    int offsetX{0};
    std::uint32_t lastStepAtMs{0};
    std::uint8_t frameBuffer[8]{0};
};
