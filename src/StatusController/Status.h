//
// Created by Piotr Rudnicki on 20/04/2026.
//

#ifndef AGENTNOTIFICATOR_STATUS_H
#define AGENTNOTIFICATOR_STATUS_H
enum class Status {
    Invalid = -1,
    Idle,
    Working,
    Finished,
    Error
};
#endif //AGENTNOTIFICATOR_STATUS_H