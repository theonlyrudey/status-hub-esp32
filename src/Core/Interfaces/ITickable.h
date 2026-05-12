//
// Created by Piotr Rudnicki on 06/05/2026.
//

#pragma once
#include <cstdint>

namespace statushub {

class ITickable {
public:
    virtual ~ITickable() = default;
    virtual void tick(std::uint32_t nowMs) = 0;
};

} // namespace statushub
