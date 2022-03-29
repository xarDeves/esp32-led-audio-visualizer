#include "AnalogManager.h"

AnalogManager::AnalogManager(Colors::RGB &clrRGB, bool &fftMode) : 
//ADC interference is plain fucking stupid,
//any logical normalization value in potNormalizers just colapses after some secs
//and using high values results in a not smooth transition of colors.
//Need to improve hardware before moving to software
potRNorm(4095, 255, 400),
potGNorm(4095, 255, 400),
potBNorm(4095, 255, 400){

    this->clrRGB = &clrRGB;
    this->fftMode = &fftMode;
}

void AnalogManager::readAnalog(){

    this->readPotentiometers();
    this->readButtons();
}

void AnalogManager::readPotentiometers(){

    this->newR = this->potRNorm.getOutputLevel(analogRead(R_ANALOG_PIN));
    this->newG = this->potGNorm.getOutputLevel(analogRead(G_ANALOG_PIN));
    this->newB = this->potBNorm.getOutputLevel(analogRead(B_ANALOG_PIN));

    //this->newR = map(this->potNormaliser.getOutputLevel(analogRead(R_ANALOG_PIN)), 0, 4095, 0 ,255);
    //this->newG = map(this->potNormaliser.getOutputLevel(analogRead(G_ANALOG_PIN)), 0, 4095, 0 ,255);
    //this->newB = map(this->potNormaliser.getOutputLevel(analogRead(B_ANALOG_PIN)), 0, 4095, 0 ,255);

    /*
    Serial.print(this->newR);
    Serial.print(',');
    Serial.print(this->newG);
    Serial.print(',');
    Serial.print(this->newB);
    Seial.println('.');
    */

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

void AnalogManager::readButtons(){}

AnalogManager::~AnalogManager(){}
