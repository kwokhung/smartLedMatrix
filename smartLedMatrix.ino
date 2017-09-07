#include "App.h"

App app;

void setup()
{
    app.setup();

    for (int i = 0; i < 256; i++)
    {
        LedMatrix::displayMatrix[i] = 0xFF;
    };

    for (int i = 0; i < LedMatrix::columnSize; i++)
    {
        app.getLedMatrix()->putCharToDisplayMatrix(i,
                                                   0,
                                                   LedMatrix::columnSize - i,
                                                   false);
    };
};

void loop(){
    //app.getLedMatrix()->loop();
};

ISR(TIMER2_COMPA_vect)
{
    LedMatrix::scan();
};
