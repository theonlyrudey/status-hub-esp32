//
// Created by Piotr Rudnicki on 06/05/2026.
//

#pragma once
#include <cstdint>

class ITickable {
public:
    virtual ~ITickable() = default;
    virtual void tick(uint32_t nowMs) = 0;
};
