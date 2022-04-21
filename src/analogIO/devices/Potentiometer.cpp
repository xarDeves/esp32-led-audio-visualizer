#include "Potentiometer.h"

Potentiometer::Potentiometer(unsigned char filterBuffLen, unsigned char gpioPin): 
DeviationFilter(filterBuffLen), pin(gpioPin){}

void Potentiometer::read(){

    raw = analogRead(pin);
    deviate(raw);
}

int Potentiometer::mapRaw(int val){

    return map(raw, 0, 4095, 0 , val);
}

Potentiometer::~Potentiometer(){}
