//
// Created by Piotr Rudnicki on 20/04/2026.
//

#ifndef AGENTNOTIFICATOR_ISTATUSLISTENER_H
#define AGENTNOTIFICATOR_ISTATUSLISTENER_H
#include "StatusEvent.h"

class IStatusListener {
public:
    virtual ~IStatusListener() = default;
    virtual void onStatusChanged(StatusEvent newStatus) = 0;
};
#endif //AGENTNOTIFICATOR_ISTATUSLISTENER_H