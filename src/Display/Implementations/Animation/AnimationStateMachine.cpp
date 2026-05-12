//
// Created by Piotr Rudnicki on 07/05/2026.
//

#include "Display/Implementations/Animation/AnimationStateMachine.h"

using namespace statushub;

AnimationStateMachine::AnimationStateMachine(const AnimationSequence *sequence, const std::uint32_t nowMs) {
    setSequence(sequence, nowMs);
}

void AnimationStateMachine::setSequence(const AnimationSequence *sequence, const std::uint32_t nowMs,
                                        const bool restart) {
    if (!restart && sequence == _sequence) {
        return;
    }

    _sequence = sequence;
    if (!hasValidSequence()) {
        clearSequence();
        return;
    }

    moveToFirstFrame(nowMs);
    _running = true;
    _finished = false;
}

void AnimationStateMachine::clearSequence() {
    _sequence = nullptr;
    _frameIndex = 0;
    _frameStartedAtMs = 0U;
    _running = false;
    _finished = false;
}

void AnimationStateMachine::restart(const std::uint32_t nowMs) {
    if (!hasValidSequence()) {
        return;
    }

    moveToFirstFrame(nowMs);
    _running = true;
    _finished = false;
}

bool AnimationStateMachine::tick(const std::uint32_t nowMs) {
    if (!_running || !hasValidSequence()) {
        return false;
    }

    bool frameChanged = false;
    std::uint32_t elapsedMs = nowMs - _frameStartedAtMs;

    while (_running) {
        const AnimationFrame *frame = currentFrame();
        if (frame == nullptr) {
            clearSequence();
            return frameChanged;
        }

        const std::uint32_t currentFrameDuration = frameDurationMs(*frame);
        if (elapsedMs < currentFrameDuration) {
            break;
        }

        elapsedMs -= currentFrameDuration;
        _frameStartedAtMs += currentFrameDuration;
        frameChanged = true;

        if (_frameIndex + 1U < _sequence->frameCount) {
            ++_frameIndex;
            continue;
        }

        if (_sequence->loopMode == LoopMode::Loop) {
            _frameIndex = 0;
            continue;
        }

        _running = false;
        _finished = true;
    }

    return frameChanged;
}

const AnimationFrame *AnimationStateMachine::currentFrame() const {
    if (!hasValidSequence() || _frameIndex >= _sequence->frameCount) {
        return nullptr;
    }

    return &_sequence->frames[_frameIndex];
}

std::size_t AnimationStateMachine::frameIndex() const {
    return _frameIndex;
}

bool AnimationStateMachine::isRunning() const {
    return _running;
}

bool AnimationStateMachine::isFinished() const {
    return _finished;
}

std::uint32_t AnimationStateMachine::frameDurationMs(const AnimationFrame &frame) {
    // Zero-duration frames would otherwise create an infinite advance loop.
    return frame.durationMs == 0U ? 1U : frame.durationMs;
}

bool AnimationStateMachine::hasValidSequence() const {
    return _sequence != nullptr && _sequence->frames != nullptr && _sequence->frameCount > 0U;
}

void AnimationStateMachine::moveToFirstFrame(const std::uint32_t nowMs) {
    _frameIndex = 0U;
    _frameStartedAtMs = nowMs;
}
