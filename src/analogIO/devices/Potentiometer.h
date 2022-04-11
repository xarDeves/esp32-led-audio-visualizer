#pragma once

#include <Arduino.h>
#include "../filter/DeviationFilter.h"

class Potentiometer : DeviationFilter{

public:
    Potentiometer(unsigned char filterBuffLen, unsigned char gpioPin);

    unsigned short raw; 
    unsigned short deviated;
    
    void read();
    int mapRaw(int val);

    ~Potentiometer();

private:
    unsigned char pin;
};
