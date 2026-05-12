//
// Created by Piotr Rudnicki on 12/05/2026.
//

#include "Display/Implementations/OledStatusListener.h"

using namespace statushub;

#include "Icons.h"

OledStatusListener::OledStatusListener(AnimationController& animationController)
    : _animationController(animationController) {}

void OledStatusListener::onStatusChanged(const StatusEvent newStatus) {
    if (newStatus.message[0] != '\0') {
        _animationController.setScene(NotificationBitmapDetailedView{
            statusBitmap(newStatus.status),
            statusLabel(newStatus.status),
            newStatus.message,
            1
        });
        return;
    }

    _animationController.setScene(NotificationBitmapDetailedView{
        statusBitmap(newStatus.status),
        statusLabel(newStatus.status),
        std::string("src: ") + newStatus.source,
        1
    });
}

const std::uint8_t* OledStatusListener::statusBitmap(const Status status) {
    switch (status) {
        case Status::Idle:
            return Icons::Idle;
        case Status::Working:
            return Icons::Working_0;
        case Status::Finished:
            return Icons::Finished;
        case Status::Error:
            return Icons::Error;
        case Status::Invalid:
        default:
            return Icons::Error;
    }
}

const char* OledStatusListener::statusLabel(const Status status) {
    switch (status) {
        case Status::Idle:
            return "IDLE";
        case Status::Working:
            return "WORKING";
        case Status::Finished:
            return "FINISHED";
        case Status::Error:
            return "ERROR";
        case Status::Invalid:
        default:
            return "INVALID";
    }
}
