//
// Created by Piotr Rudnicki on 06/05/2026.
//

#ifndef AGENTNOTIFICATOR_APPRUNTIME_H
#define AGENTNOTIFICATOR_APPRUNTIME_H
#include <vector>

#include "ITickable.h"

class AppRuntime {
public:
    void registerTickable(ITickable* tickable);
    void unregisterTickable(ITickable* tickable);
    void loop() const;

private:
    std::vector<ITickable*> _tickables;
};


#endif //AGENTNOTIFICATOR_APPRUNTIME_H
