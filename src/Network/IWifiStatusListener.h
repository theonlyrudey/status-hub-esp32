//
// Created by Piotr Rudnicki on 08/05/2026.
//

#pragma once

#include "WifiTypes.h"

class IWifiStatusListener {
public:
    virtual ~IWifiStatusListener() = default;
    virtual void onWifiStatusChanged(const WifiStatusEvent& event) = 0;
};
