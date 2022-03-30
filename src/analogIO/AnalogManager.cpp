#include "AnalogManager.h"

AnalogManager::AnalogManager(Colors::RGB &clrRGB, bool &fftMode)
 : rPotFilter(BUFF_LEN), gPotFilter(BUFF_LEN), bPotFilter(BUFF_LEN){

    this->clrRGB = &clrRGB;
    this->fftMode = &fftMode;
}

void AnalogManager::read(){

    this->readPotentiometers();
    this->readButtons();
}

void AnalogManager::readPotentiometers(){

    unsigned short rRaw = analogRead(R_ANALOG_PIN);
    unsigned short gRaw = analogRead(G_ANALOG_PIN);
    unsigned short bRaw = analogRead(B_ANALOG_PIN);

    if (rPotFilter.deviate(rRaw) > DEVIATION_MAX || 
        gPotFilter.deviate(gRaw) > DEVIATION_MAX || 
        bPotFilter.deviate(bRaw) > DEVIATION_MAX){

        this->clrRGB->r = map(rRaw, 0, 4095, 0 ,255);
        this->clrRGB->g = map(gRaw, 0, 4095, 0 ,255);
        this->clrRGB->b = map(bRaw, 0, 4095, 0 ,255);
    }
    
}

void AnalogManager::readButtons(){}

AnalogManager::~AnalogManager(){}
