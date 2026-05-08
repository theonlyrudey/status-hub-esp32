//
// Created by Piotr Rudnicki on 08/05/2026.
//

#pragma once

enum class WifiState;

class IWifiStatusListener {
public:
    virtual ~IWifiStatusListener() = default;
    virtual void onWifiStatusChanged(WifiState state) = 0;
};
