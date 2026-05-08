//
// Created by Piotr Rudnicki on 07/05/2026.
//

#ifndef AGENTNOTIFICATOR_ANIMATIONSTATEMACHINE_H
#define AGENTNOTIFICATOR_ANIMATIONSTATEMACHINE_H

#include <cstddef>
#include <cstdint>

#include "AnimationSequence.h"

class AnimationStateMachine {
public:
    AnimationStateMachine() = default;
    explicit AnimationStateMachine(const AnimationSequence *sequence, std::uint32_t nowMs = 0U);

    void setSequence(const AnimationSequence *sequence, std::uint32_t nowMs, bool restart = true);
    void clearSequence();
    void restart(std::uint32_t nowMs);

    bool tick(std::uint32_t nowMs);

    const AnimationFrame *currentFrame() const;
    std::size_t frameIndex() const;
    bool isRunning() const;
    bool isFinished() const;

private:
    static std::uint32_t frameDurationMs(const AnimationFrame &frame);
    bool hasValidSequence() const;
    void moveToFirstFrame(std::uint32_t nowMs);

    const AnimationSequence *_sequence{nullptr};
    std::size_t _frameIndex{0};
    std::uint32_t _frameStartedAtMs{0U};
    bool _running{false};
    bool _finished{false};
};

#endif //AGENTNOTIFICATOR_ANIMATIONSTATEMACHINE_H
