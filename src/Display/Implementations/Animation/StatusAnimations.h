//
// Created by Piotr Rudnicki on 07/05/2026.
//

#pragma once
#include "Display/Implementations/Animation/AnimationSequence.h"
#include "StatusController/Implementations/Status.h"


namespace statushub {

namespace StatusAnimations {
    const AnimationSequence* sequenceForStatus(Status status);
    const AnimationFrame* frameForStatus(Status status);
};



} // namespace statushub
