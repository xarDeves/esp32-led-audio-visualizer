#pragma once

#include <Arduino.h>
#include "Smoother.h"

#define NOISE 200
#define MAX 150000

class Band : public Smoother{

public:
    Band(unsigned char &lower, unsigned char &upper, unsigned char &smoothingLen, double *vReal);

    void adjustLimits(unsigned char &lower, unsigned char &upper);
    
    unsigned char renderRGB();
    //unsigned char renderHue();
    //unsigned char renderSaturation();
    //unsigned char renderValue();
    //unsigned char renderLightness();

    ~Band();

private:
    double *vReal;
    unsigned char *upper;
    unsigned char *lower;

    double bandSum;
    float devider;

    void sumBand();
    void computeDevider();
};