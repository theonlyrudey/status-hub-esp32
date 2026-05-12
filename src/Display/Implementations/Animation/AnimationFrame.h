//
// Created by Piotr Rudnicki on 07/05/2026.
//

#pragma once
#include <cstdint>

namespace statushub {

struct AnimationFrame {
    const std::uint8_t *bitmap;
    std::uint32_t durationMs;
};

} // namespace statushub
