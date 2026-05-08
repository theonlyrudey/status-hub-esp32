//
// Created by Piotr Rudnicki on 07/05/2026.
//

#pragma once
#include "AnimationSequence.h"
#include "StatusController/Status.h"


namespace StatusAnimations {
    const AnimationSequence* sequenceForStatus(Status status);
    const AnimationFrame* frameForStatus(Status status);
};


