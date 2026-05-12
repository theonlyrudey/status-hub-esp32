//
// Created by Piotr Rudnicki on 11/05/2026.
//

#pragma once
#include <ESPmDNS.h>
#include "Network/Interfaces/IWifiStatusListener.h"

namespace statushub {

class MdnsService : public IWifiStatusListener {
public:
    explicit MdnsService(const String &hostname);
    void onWifiStatusChanged(const WifiStatusEvent& event) override;

private:
    void begin();
    void stop();

    MDNSResponder _mdnsResponder;
    String _hostname;
    bool _isRunning = false;
};

} // namespace statushub
