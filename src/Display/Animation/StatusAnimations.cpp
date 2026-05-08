//
// Created by Piotr Rudnicki on 07/05/2026.
//

#include "StatusAnimations.h"

#include "Icons.h"

namespace StatusAnimations {
    static constexpr AnimationFrame IDLE_FRAMES[] = {
        {Icons::Idle, 1000U }
    };

    static constexpr AnimationFrame WORKING_FRAMES[] = {
        {Icons::Working_0, 250U },
        {Icons::Working_1, 250U },
        {Icons::Working_2, 250U }
    };

    static constexpr AnimationFrame FINISHED_FRAMES[] = {
        {Icons::Finished, 1000U}
    };

    static constexpr AnimationFrame ERROR_FRAMES[] = {
        {Icons::Error, 1000U}
    };

    static constexpr AnimationSequence IDLE_SEQUENCE {
        IDLE_FRAMES,
        sizeof(IDLE_FRAMES) / sizeof(AnimationFrame),
        LoopMode::Loop
    };

    static constexpr AnimationSequence WORKING_SEQUENCE {
        WORKING_FRAMES,
        sizeof(WORKING_FRAMES) / sizeof(AnimationFrame),
        LoopMode::Loop
    };

    static constexpr AnimationSequence FINISHED_SEQUENCE {
        FINISHED_FRAMES,
        sizeof(FINISHED_FRAMES) / sizeof(AnimationFrame),
        LoopMode::Once
    };

    static constexpr AnimationSequence ERROR_SEQUENCE {
        ERROR_FRAMES,
        sizeof(ERROR_FRAMES) / sizeof(AnimationFrame),
        LoopMode::Once
    };

    const AnimationSequence* sequenceForStatus(const Status status) {
        switch (status) {
            case Status::Idle: return &IDLE_SEQUENCE;
            case Status::Invalid: return nullptr;
            case Status::Working: return &WORKING_SEQUENCE;
            case Status::Finished: return &FINISHED_SEQUENCE;
            case Status::Error: return &ERROR_SEQUENCE;
        }
        return nullptr;
    }

    const AnimationFrame* frameForStatus(const Status status) {
        switch (status) {
            case Status::Idle: return &IDLE_FRAMES[0];
            case Status::Invalid: return nullptr;
            case Status::Working: return &WORKING_FRAMES[0];
            case Status::Finished: return &FINISHED_FRAMES[0];
            case Status::Error: return &ERROR_FRAMES[0];
        }
        return nullptr;
    }
}
