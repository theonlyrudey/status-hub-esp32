//
// Created by Piotr Rudnicki on 12/05/2026.
//

#pragma once

#include "Display/Implementations/Animation/AnimationController.h"
#include "StatusController/Interfaces/IStatusListener.h"

namespace statushub {

class OledStatusListener : public IStatusListener {
public:
    explicit OledStatusListener(AnimationController& animationController);
    void onStatusChanged(StatusEvent newStatus) override;

private:
    static const std::uint8_t* statusBitmap(Status status);
    static const char* statusLabel(Status status);

    AnimationController& _animationController;
};

} // namespace statushub
