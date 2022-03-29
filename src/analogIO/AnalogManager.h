#pragma once

#include <Arduino.h>
#include "colorUtils/Colors.h"
#include "HystFilter.h"

#define FILTER_LEN 40

#define R_ANALOG_PIN 32 //GPIO 33
#define G_ANALOG_PIN 33 //GPIO 32
#define B_ANALOG_PIN 35 //GPIO 35

class AnalogManager{

public:
    AnalogManager(Colors::RGB &clrRGB, bool &fftMode);

    void readAnalog();

    ~AnalogManager();
    
private:
	bool *fftMode;
    Colors::RGB *clrRGB;

    HystFilter potRNorm;
    HystFilter potGNorm;
    HystFilter potBNorm;

    unsigned char newR = 0;
    unsigned char newG = 0;
    unsigned char newB = 0;

    unsigned char prevR = 0;
    unsigned char prevG = 0;
    unsigned char prevB = 0;

    void readPotentiometers();
    void readButtons();
};
