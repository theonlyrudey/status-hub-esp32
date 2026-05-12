//
// Created by Piotr Rudnicki on 07/05/2026.
//

#include "Display/Implementations/MatrixStatusListener.h"

using namespace statushub;

#include "Display/Implementations/Animation/StatusAnimations.h"

MatrixStatusListener::MatrixStatusListener(AnimationController& animationController) : _animationController(animationController) {}

void MatrixStatusListener::onStatusChanged(const StatusEvent newStatus) {
    switch (_mode) {
        case AnimationMode::None:
            break;
        case AnimationMode::Sequence:
            setAnimationSequence(newStatus);
            break;
        case AnimationMode::ScrollBitmap:
            setAnimationScrollBitmap(newStatus);
            break;
    }
}

void MatrixStatusListener::setAnimationMode(const AnimationMode mode, const bool wrap) {
    _mode = mode;
    _wrap = wrap;
}

void MatrixStatusListener::setAnimationSequence(const StatusEvent &newStatus) const {
    const AnimationSequence* seq = StatusAnimations::sequenceForStatus(newStatus.status);
    if (seq == nullptr) {
        _animationController.stop();
        return;
    }
    _animationController.setSequence(seq, newStatus.receivedAtMs, true);
}

void MatrixStatusListener::setAnimationScrollBitmap(const StatusEvent &newStatus) const {
    const AnimationFrame* frame = StatusAnimations::frameForStatus(newStatus.status);
    if (frame == nullptr) {
        _animationController.stop();
        return;
    }
    _animationController.setScrollingBitmap(frame->bitmap, newStatus.receivedAtMs, frame->durationMs, 1, _wrap);
}
