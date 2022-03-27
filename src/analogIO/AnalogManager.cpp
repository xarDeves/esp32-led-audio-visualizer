#include "AnalogManager.h"

AnalogManager::AnalogManager( Colors::RGB &clrRgb, bool &fftMode){

    this->clrRgb = &clrRgb;
    this->fftMode = &fftMode;
}

void AnalogManager::readAnalog(){

}

AnalogManager::~AnalogManager(){}