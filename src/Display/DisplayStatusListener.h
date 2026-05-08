//
// Created by Piotr Rudnicki on 07/05/2026.
//

#ifndef AGENTNOTIFICATOR_DISPLAYSTATUSLISTENER_H
#define AGENTNOTIFICATOR_DISPLAYSTATUSLISTENER_H
#include "Animation/AnimationController.h"
#include "StatusController/IStatusListener.h"


class DisplayStatusListener : public IStatusListener {
public:
    explicit DisplayStatusListener(AnimationController& animationController);
    void onStatusChanged(StatusEvent newStatus) override;
    void setAnimationMode(AnimationMode mode, bool wrap = false);

private:
    void setAnimationSequence(const StatusEvent &newStatus) const;
    void setAnimationScrollBitmap(const StatusEvent &newStatus) const;

    AnimationController& _animationController;
    AnimationMode _mode = AnimationMode::None;
    bool _wrap = false;
};


#endif //AGENTNOTIFICATOR_DISPLAYSTATUSLISTENER_H
