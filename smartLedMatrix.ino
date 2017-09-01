#include "App.h"

App app;

void setup()
{
    app.setup();
};

void loop()
{
    app.getLedMatrix()->loop();
};

ISR(TIMER2_COMPA_vect)
{
    app.getLedMatrix()->scan();
};
