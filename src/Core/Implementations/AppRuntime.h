//
// Created by Piotr Rudnicki on 06/05/2026.
//

#pragma once
#include <vector>

#include "Core/Interfaces/ITickable.h"

namespace statushub {

class AppRuntime {
public:
    void registerTickable(ITickable* tickable);
    void unregisterTickable(ITickable* tickable);
    void loop() const;

private:
    std::vector<ITickable*> _tickables;
};



} // namespace statushub
