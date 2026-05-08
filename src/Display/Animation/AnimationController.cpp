//
// Created by Piotr Rudnicki on 07/05/2026.
//

#include "AnimationController.h"
#include "Display/IDisplayBackend.h"

AnimationController::AnimationController(IDisplayBackend &displayBackend) : _displayBackend(displayBackend) {
}

void AnimationController::tick(const std::uint32_t nowMs) {
    switch (_mode) {
        case AnimationMode::Sequence:
            tickSequence(nowMs);
            break;
        case AnimationMode::ScrollBitmap:
            tickScrollBitmap(nowMs);
            break;
        case AnimationMode::None:
        default:
            break;
    }
}

void AnimationController::setSequence(const AnimationSequence *sequence, const std::uint32_t nowMs, const bool restart) {
    _mode = AnimationMode::Sequence;
    _stateMachine.setSequence(sequence, nowMs, restart);
    _needsRender = true;
}

void AnimationController::setScrollingBitmap(const std::uint8_t *bitmap, const std::uint32_t nowMs, const std::uint32_t stepMs, const std::int8_t direction, const bool wrap) {
    if (bitmap == nullptr) {
        stop();
        return;
    }

    _stateMachine.clearSequence();
    _mode = AnimationMode::ScrollBitmap;

    _scrollState.sourceBitmap = bitmap;
    _scrollState.stepMs = stepMs == 0U ? 1U : stepMs;
    _scrollState.direction = direction >= 0 ? 1 : -1;
    _scrollState.wrap = wrap;
    _scrollState.offsetX = _scrollState.wrap ? 0 : (_scrollState.direction < 0 ? 7 : -7);
    _scrollState.lastStepAtMs = nowMs;

    _needsRender = true;
}

void AnimationController::stop() {
    _mode = AnimationMode::None;
    _stateMachine.clearSequence();
    _scrollState = ScrollState{};
    _needsRender = false;
    _displayBackend.clear();
}

void AnimationController::tickSequence(const std::uint32_t nowMs) {
    const bool changed = _stateMachine.tick(nowMs);
    if (!_needsRender && !changed) return;

    if (const AnimationFrame* frame = _stateMachine.currentFrame(); frame != nullptr) {
        _displayBackend.render(Bitmap8x8View{frame->bitmap});
        _needsRender = false;
    }
}

void AnimationController::tickScrollBitmap(const std::uint32_t nowMs) {
    if (_scrollState.sourceBitmap == nullptr) return;

    bool changed = _needsRender;
    const std::uint32_t step = _scrollState.stepMs == 0U ? 1U : _scrollState.stepMs;

    while (nowMs - _scrollState.lastStepAtMs >= step) {
        _scrollState.lastStepAtMs += step;
        _scrollState.offsetX += _scrollState.direction;

        if (_scrollState.wrap) {
            _scrollState.offsetX = (_scrollState.offsetX % 8 + 8) % 8;
        } else {
            if (_scrollState.direction < 0 && _scrollState.offsetX < -7) {
                _scrollState.offsetX = 7;
            } else if (_scrollState.direction > 0 && _scrollState.offsetX > 7) {
                _scrollState.offsetX = -7;
            }
        }

        changed = true;
    }

    if (!changed) return;

    buildShiftedBitmap(_scrollState.sourceBitmap, _scrollState.offsetX, _scrollState.wrap, _scrollState.frameBuffer);
    _displayBackend.render(Bitmap8x8View{_scrollState.frameBuffer});
    _needsRender = false;
}

void AnimationController::buildShiftedBitmap(const std::uint8_t src[8], const int offsetX, const bool wrap, std::uint8_t dest[8]) {
    for (int y = 0; y < 8; ++y) dest[y] = 0;
    for (int y = 0; y < 8; ++y) {
        for (int xDest = 0; xDest < 8; ++xDest) {
            int xSrc = xDest - offsetX;
            if (wrap) {
                xSrc = (xSrc % 8 + 8) % 8;
            }
            if (xSrc < 0 || xSrc > 7) continue;

            const bool on = (src[y] & (1u << (7 - xSrc))) != 0;
            if (on) dest[y] |= static_cast<std::uint8_t>(1u << (7 - xDest));
        }
    }
}
