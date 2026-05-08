//
// Created by Piotr Rudnicki on 06/05/2026.
//

#pragma once
#include <WString.h>
#include "Status.h"


class StatusCodec {
public:
    static bool tryParseStatus(const String&, Status&);
    static const char* toString(Status);
};


