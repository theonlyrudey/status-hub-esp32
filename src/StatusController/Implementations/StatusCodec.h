//
// Created by Piotr Rudnicki on 06/05/2026.
//

#pragma once
#include <WString.h>
#include "StatusController/Implementations/Status.h"


namespace statushub {

class StatusCodec {
public:
    static bool tryParseStatus(const String&, Status&);
    static const char* toString(Status);
};



} // namespace statushub
