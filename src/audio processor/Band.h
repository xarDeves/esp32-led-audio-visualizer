#pragma once

#include "debug.h"

#include <Arduino.h>
#include "Smoother.h"

//TODO deprecate noise
class Band : public Smoother{

public:
    Band(unsigned char &lower, unsigned char &upper, unsigned char &smoothingLen, unsigned int  &noise, double *vReal);

    double sumBand();
    void adjustNoise(unsigned int  &noise);
    void adjustLimits(unsigned char &lower, unsigned char &upper);
    
    ~Band();

private:
    double *vReal;
    unsigned char *upper;
    unsigned char *lower;

    float devider;
    unsigned int *noise;

    void computeDevider();
};