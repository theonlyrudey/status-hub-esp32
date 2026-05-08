//
// Created by Piotr Rudnicki on 06/05/2026.
//

#ifndef AGENTNOTIFICATOR_ITICKABLE_H
#define AGENTNOTIFICATOR_ITICKABLE_H
#include <cstdint>

class ITickable {
public:
    virtual ~ITickable() = default;
    virtual void tick(uint32_t nowMs) = 0;
};
#endif //AGENTNOTIFICATOR_ITICKABLE_H
