#include <Arduino.h>
#include "Core/StatusHubApp.h"

StatusHubApp app;

void setup()
{
    app.begin();
}

void loop()
{
    app.loop();
}
