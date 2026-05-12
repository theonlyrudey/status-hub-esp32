//
// Created by Piotr Rudnicki on 07/05/2026.
//

#pragma once
#include <cstdint>

#include "Display/Implementations/Animation/AnimationStateMachine.h"
#include "Display/Implementations/Animation/ScrollState.h"
#include "Core/Interfaces/ITickable.h"
#include "Display/Interfaces/IDisplayBackend.h"


namespace statushub {

class IDisplayBackend;

enum class AnimationMode : std::uint8_t { None, Sequence, ScrollBitmap, StaticScene };

class AnimationController : public ITickable {
public:
    explicit AnimationController(IDisplayBackend &displayBackend);
    void tick(std::uint32_t nowMs) override;

    void setSequence(const AnimationSequence *sequence, std::uint32_t nowMs, bool restart = true);
    void setScrollingBitmap(const std::uint8_t* bitmap, std::uint32_t nowMs, std::uint32_t stepMs = 250U, std::int8_t direction = 1, bool wrap = true);
    void setScene(const DisplayScene& scene);
    void stop();

private:
    static void buildShiftedBitmap(const std::uint8_t src[8], int offsetX, bool wrap, std::uint8_t dest[8]);

    void tickSequence(std::uint32_t nowMs);
    void tickScrollBitmap(std::uint32_t nowMs);
    void tickStaticScene();

    AnimationStateMachine _stateMachine;
    IDisplayBackend &_displayBackend;
    AnimationMode _mode{AnimationMode::None};
    ScrollState _scrollState{};
    DisplayScene _scene{TextLine{""}};
    bool _needsRender{false};
};

} // namespace statushub
