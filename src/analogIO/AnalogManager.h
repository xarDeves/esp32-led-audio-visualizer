#pragma once

#include <Arduino.h>
#include "colorUtils/Colors.h"
#include "filter/DeviationFilter.h"

#define BUFF_LEN 200
#define DEVIATION_MAX 30

#define PIN_1 33
#define PIN_2 32
#define PIN_3 35

class AnalogManager{

public:
    AnalogManager(Colors::RGB &clrRGB, bool &fftMode);

    void read();

    ~AnalogManager();
    
private:
	bool *fftMode;
    Colors::RGB *clrRGB;

    unsigned short raw1;
    unsigned short raw2;
    unsigned short raw3;

    DeviationFilter pot1Filter;
    DeviationFilter pot2Filter;
    DeviationFilter pot3Filter;

    void readPotentiometers();
    void readButtons();

    bool inputEligible();
    void changeColors();
    void changeBands();
};
