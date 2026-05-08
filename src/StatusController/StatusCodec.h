//
// Created by Piotr Rudnicki on 06/05/2026.
//

#ifndef AGENTNOTIFICATOR_STATUSCODEC_H
#define AGENTNOTIFICATOR_STATUSCODEC_H
#include <WString.h>
#include "Status.h"


class StatusCodec {
public:
    static bool tryParseStatus(const String&, Status&);
    static const char* toString(Status);
};


#endif //AGENTNOTIFICATOR_STATUSCODEC_H
