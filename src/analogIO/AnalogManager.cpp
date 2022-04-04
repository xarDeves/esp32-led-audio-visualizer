#include "AnalogManager.h"

AnalogManager::AnalogManager(Colors::RGB &clrRGB, bool &fftMode)
 : pot1Filter(BUFF_LEN), pot2Filter(BUFF_LEN), pot3Filter(BUFF_LEN){

    this->clrRGB = &clrRGB;
    this->fftMode = &fftMode;
}

void AnalogManager::read(){

    readButtons();
    readPotentiometers();
}

void AnalogManager::readPotentiometers(){

    raw1 = analogRead(PIN_1);
    raw2 = analogRead(PIN_2);
    raw3 = analogRead(PIN_3);

    if (inputEligible()){
        if(*fftMode) changeBands();
        else changeColors();
    }

}

inline bool AnalogManager::inputEligible(){

    if (pot1Filter.deviate(raw1) > DEVIATION_MAX || 
        pot2Filter.deviate(raw2) > DEVIATION_MAX || 
        pot3Filter.deviate(raw3) > DEVIATION_MAX) return true;
    return false;
}

inline void AnalogManager::changeBands(){

}

inline void AnalogManager::changeColors(){

    clrRGB->r = map(raw1, 0, 4095, 0 ,255);
    clrRGB->g = map(raw2, 0, 4095, 0 ,255);
    clrRGB->b = map(raw3, 0, 4095, 0 ,255);
}

void AnalogManager::readButtons(){}

AnalogManager::~AnalogManager(){}
