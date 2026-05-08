#include <Arduino.h>
#include <MD_MAX72xx.h>
#include "Core/AppRuntime.h"
#include "Display/DisplayStatusListener.h"
#include "Display/MatrixDisplayBackend.h"
#include "Display/Animation/AnimationController.h"
#include "StatusController/StatusController.h"

#define HARDWARE_TYPE MD_MAX72XX::GENERIC_HW
#define MAX_DEVICES 1
#define CS_PIN 5

MD_MAX72XX mx(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);
StatusController statusController;
AppRuntime appRuntime;

MatrixDisplayBackend matrixDisplayBackend(mx);
AnimationController animationController(matrixDisplayBackend);
DisplayStatusListener displayStatusListener(animationController);

void setup()
{
    matrixDisplayBackend.init();
    displayStatusListener.setAnimationMode(AnimationMode::Sequence, false);

    statusController.addListener(&displayStatusListener);
    appRuntime.registerTickable(&animationController);
    statusController.setStatus(StatusEvent(Status::Idle, millis(), "setup") );
}

void loop()
{
    appRuntime.loop();
}
