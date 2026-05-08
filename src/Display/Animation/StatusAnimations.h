//
// Created by Piotr Rudnicki on 07/05/2026.
//

#ifndef AGENTNOTIFICATOR_STATUSANIMATIONS_H
#define AGENTNOTIFICATOR_STATUSANIMATIONS_H
#include "AnimationSequence.h"
#include "StatusController/Status.h"


namespace StatusAnimations {
    const AnimationSequence* sequenceForStatus(Status status);
    const AnimationFrame* frameForStatus(Status status);
};


#endif //AGENTNOTIFICATOR_STATUSANIMATIONS_H
