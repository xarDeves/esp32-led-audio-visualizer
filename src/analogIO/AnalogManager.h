#pragma once

#include <Arduino.h>
#include "colorUtils/Colors.h"
#include "filter/DeviationFilter.h"

#define BUFF_LEN 200
#define DEVIATION_MAX 30

#define R_ANALOG_PIN 32 //GPIO 33
#define G_ANALOG_PIN 33 //GPIO 32
#define B_ANALOG_PIN 35 //GPIO 35

class AnalogManager{

public:
    AnalogManager(Colors::RGB &clrRGB, bool &fftMode);

    void read();

    ~AnalogManager();
    
private:
	bool *fftMode;
    Colors::RGB *clrRGB;

    DeviationFilter rPotFilter;
    DeviationFilter gPotFilter;
    DeviationFilter bPotFilter;

    void readPotentiometers();
    void readButtons();
};
