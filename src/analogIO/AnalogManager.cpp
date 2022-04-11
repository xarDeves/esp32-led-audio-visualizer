#include "AnalogManager.h"

AnalogManager::AnalogManager(Model &model, Controller &controller)
 : pot1(BUFF_LEN, PIN_1), pot2(BUFF_LEN, PIN_2), pot3(BUFF_LEN, PIN_3){

    this->model = &model;
    this->controller = &controller;
}

void AnalogManager::read(){

    readButtons();
    readPotentiometers();
}

void AnalogManager::readPotentiometers(){

    pot1.read();
    pot2.read();
    pot3.read();

    //READ AND SET FFT BUTTON
    if (model->fftMode) {
        controller->FFTOn();
    }
    else {
        controller->FFTOff();
    }
}

inline bool AnalogManager::inputEligible(){

    if (pot1.deviated > DEVIATION_MAX || 
        pot2.deviated > DEVIATION_MAX || 
        pot3.deviated > DEVIATION_MAX) return true;
    return false;
}

void AnalogManager::assignColors(){

    model->clrRGB.r = pot1.mapRaw(MAP_MAX);
    model->clrRGB.g = pot2.mapRaw(MAP_MAX);
    model->clrRGB.b = pot3.mapRaw(MAP_MAX);
}

void AnalogManager::assignBufferLens(){
    
    model->engineInfo.rSmoothingLen = pot1.mapRaw(MAP_MAX);
    model->engineInfo.gSmoothingLen = pot2.mapRaw(MAP_MAX);
    model->engineInfo.bSmoothingLen = pot3.mapRaw(MAP_MAX);
}

void AnalogManager::pollSmoothingValues(){

    if (inputEligible()){
        assignBufferLens();
        controller->smoothingChanged();
    }
}

void AnalogManager::pollColorValues(){

    if (inputEligible()){
        assignColors();
        controller->colorChanged();
    }
}

void AnalogManager::readButtons(){}

AnalogManager::~AnalogManager(){}
