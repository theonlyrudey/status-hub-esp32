//
// Created by Piotr Rudnicki on 08/05/2026.
//

#pragma once
#include <Arduino.h>

#include "IWifiStatusListener.h"


class WifiStatusSerialListener : public IWifiStatusListener {
public:
    explicit WifiStatusSerialListener(Print& serial);
    void onWifiStatusChanged(const WifiStatusEvent& event) override;

private:
    Print& _serial;
};
