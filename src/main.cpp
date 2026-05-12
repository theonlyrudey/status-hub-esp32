#include <Arduino.h>
#include "Core/Implementations/StatusHubApp.h"

statushub::StatusHubApp app;
void setup()
{
    app.begin();
}

void loop()
{
    app.loop();
}
