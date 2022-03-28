#include "AnalogManager.h"

//fill ADC buffers with real data read from ADCs at initialization
AnalogManager::AnalogManager(Colors::RGB &clrRGB, bool &fftMode){

    this->clrRGB = &clrRGB;
    this->fftMode = &fftMode;
}

void AnalogManager::readAnalog(){

    this->readPotentiometers();
    this->readButtons();
}

void AnalogManager::readPotentiometers(){

    this->newR = this->interpolateADC(
        map(
            analogRead(R_ANALOG_PIN), 0, 4095, 0 ,255),
            this->rPotBuffer,
            this->rPotBufferCount
            );

    this->newG = this->interpolateADC(
        map(
            analogRead(G_ANALOG_PIN), 0, 4095, 0 ,255),
            this->gPotBuffer,
            this->gPotBufferCount
            );

    this->newB = this->interpolateADC(
        map(
            analogRead(B_ANALOG_PIN), 0, 4095, 0 ,255),
            this->bPotBuffer,
            this->bPotBufferCount
            );

    /*
    this->newR = map(
        this->interpolateADC(
            analogRead(R_ANALOG_PIN),
            this->rPotBuffer,
            this->rPotBufferCount
        ), 0, 4095, 0 ,255);
    
    this->newG = map(
        this->interpolateADC(
            analogRead(G_ANALOG_PIN),
            this->gPotBuffer,
            this->gPotBufferCount
        ), 0, 4095, 0 ,255);

    this->newB = map(
        this->interpolateADC(
            analogRead(B_ANALOG_PIN),
            this->bPotBuffer,
            this->bPotBufferCount
        ), 0, 4095, 0 ,255);
    */

    //this->newG = map(analogRead(G_ANALOG_PIN), 0, 4095, 0 ,255);
    //this->newB = map(analogRead(B_ANALOG_PIN), 0, 4095, 0 ,255);

    if (this->prevR != this->newR ||
        this->prevG != this->newG ||
        this->prevB != this->newB){

        this->clrRGB->r = this->newR;
        this->clrRGB->g = this->newG;
        this->clrRGB->b = this->newB;

        this->prevR = this->newR;
        this->prevG = this->newG;
        this->prevB = this->newB;
    }
    
}

int AnalogManager::interpolateADC(int raw, unsigned char *buff, unsigned char &buffCounter){

    int i = 0;
    int sum = 0;

    buff[buffCounter++] = raw;

    if(buffCounter == FILTER_LEN) buffCounter = 0;
    for(i = 0; i < FILTER_LEN; i++) sum += buff[i];

    return (sum / FILTER_LEN);
}

void AnalogManager::readButtons(){}

AnalogManager::~AnalogManager(){}