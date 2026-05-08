//
// Created by Piotr Rudnicki on 07/05/2026.
//

#pragma once
#include "AnimationStateMachine.h"
#include "ScrollState.h"
#include "Core/ITickable.h"


class IDisplayBackend;

enum class AnimationMode : uint8_t { None, Sequence, ScrollBitmap };

class AnimationController : public ITickable {
public:
    explicit AnimationController(IDisplayBackend &displayBackend);
    void tick(std::uint32_t nowMs) override;

    void setSequence(const AnimationSequence *sequence, std::uint32_t nowMs, bool restart = true);
    void setScrollingBitmap(const std::uint8_t* bitmap, std::uint32_t nowMs, uint32_t stepMs = 250U, std::int8_t direction = 1, bool wrap = true);
    void stop();

private:
    static void buildShiftedBitmap(const std::uint8_t src[8], int offsetX, bool wrap, std::uint8_t dest[8]);

    void tickSequence(std::uint32_t nowMs);
    void tickScrollBitmap(std::uint32_t nowMs);

    AnimationStateMachine _stateMachine;
    IDisplayBackend &_displayBackend;
    AnimationMode _mode{AnimationMode::None};
    ScrollState _scrollState{};
    bool _needsRender{false};
};


