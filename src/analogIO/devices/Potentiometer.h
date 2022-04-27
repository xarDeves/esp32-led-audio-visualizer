#pragma once

#include "debug.h"

#include <Arduino.h>
#include "../filter/DeviationFilter.h"

class Potentiometer : public DeviationFilter{

public:
    Potentiometer(unsigned char filterBuffLen, unsigned char gpioPin);

    unsigned short raw; 
    
    void read();
    int mapRaw(int val);

    ~Potentiometer();

private:
    unsigned char pin;
};
