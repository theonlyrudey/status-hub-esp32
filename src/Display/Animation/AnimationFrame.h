//
// Created by Piotr Rudnicki on 07/05/2026.
//

#ifndef AGENTNOTIFICATOR_ANIMATIONFRAME_H
#define AGENTNOTIFICATOR_ANIMATIONFRAME_H
#include <cstdint>

struct AnimationFrame {
    const std::uint8_t *bitmap;
    std::uint32_t durationMs;
};
#endif //AGENTNOTIFICATOR_ANIMATIONFRAME_H
