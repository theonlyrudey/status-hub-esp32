//
// Created by Piotr Rudnicki on 08/05/2026.
//

#pragma once

#include "Network/Interfaces/WifiTypes.h"

namespace statushub {

class IWifiStatusListener {
public:
    virtual ~IWifiStatusListener() = default;
    virtual void onWifiStatusChanged(const WifiStatusEvent& event) = 0;
};

} // namespace statushub
