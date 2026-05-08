//
// Created by Piotr Rudnicki on 07/05/2026.
//

#ifndef AGENTNOTIFICATOR_ANIMATIONSEQUENCE_H
#define AGENTNOTIFICATOR_ANIMATIONSEQUENCE_H
#include <cstddef>
#include <cstdint>

#include "AnimationFrame.h"

enum class LoopMode : std::uint8_t { Once, Loop };

struct AnimationSequence {
    const AnimationFrame *frames{nullptr};
    std::size_t frameCount{0};
    LoopMode loopMode{LoopMode::Loop};
};
#endif //AGENTNOTIFICATOR_ANIMATIONSEQUENCE_H
