#include "AnalogManager.h"

AnalogManager::AnalogManager(Model &model, Controller &controller)
 : pot1Filter(BUFF_LEN), pot2Filter(BUFF_LEN), pot3Filter(BUFF_LEN){

    this->model = &model;
    this->controller = &controller;
}

void AnalogManager::read(){

    readButtons();
    readPotentiometers();
}

void AnalogManager::readPotentiometers(){

    raw1 = analogRead(PIN_1);
    raw2 = analogRead(PIN_2);
    raw3 = analogRead(PIN_3);

    //READ AND SET FFT BUTTON
    if (model->fftMode) {
        controller->FFTOn();
    }
    else {
        controller->FFTOff();
    }
}

inline void AnalogManager::mapRaw(){

    raw1 = map(raw1, 0, 4095, 0 ,255);
    raw2 = map(raw2, 0, 4095, 0 ,255);
    raw3 = map(raw3, 0, 4095, 0 ,255);
}

inline bool AnalogManager::inputEligible(){

    if (pot1Filter.deviate(raw1) > DEVIATION_MAX || 
        pot2Filter.deviate(raw2) > DEVIATION_MAX || 
        pot3Filter.deviate(raw3) > DEVIATION_MAX) return true;
    return false;
}

void AnalogManager::assignColors(){

        model->clrRGB.r = raw1;
        model->clrRGB.g = raw2;
        model->clrRGB.b = raw3;
}

void AnalogManager::assignBufferLens(){
    
    model->engineInfo.rSmoothingLen = (unsigned char)raw1;
    model->engineInfo.gSmoothingLen = (unsigned char)raw2;
    model->engineInfo.bSmoothingLen = (unsigned char)raw3;
}

void AnalogManager::pollSmoothingValues(){

    if (inputEligible()){
        mapRaw();
        assignBufferLens();
        controller->smoothingChanged();
    }
}

void AnalogManager::pollColorValues(){

    if (inputEligible()){
        mapRaw();
        assignColors();
        controller->colorChanged();
    }
}

void AnalogManager::readButtons(){}

AnalogManager::~AnalogManager(){}
