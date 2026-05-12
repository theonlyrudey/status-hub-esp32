//
// Created by Piotr Rudnicki on 07/05/2026.
//

#pragma once
#include <cstddef>
#include <cstdint>

#include "Display/Implementations/Animation/AnimationFrame.h"

namespace statushub {

enum class LoopMode : std::uint8_t { Once, Loop };

struct AnimationSequence {
    const AnimationFrame *frames{nullptr};
    std::size_t frameCount{0};
    LoopMode loopMode{LoopMode::Loop};
};

} // namespace statushub
