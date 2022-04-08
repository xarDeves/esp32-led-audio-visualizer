#pragma once

#include <Arduino.h>
#include "filter/DeviationFilter.h"
#include "controller/Controller.h"
#include "model/Model.h"

#define BUFF_LEN 200
#define DEVIATION_MAX 30

#define PIN_1 33
#define PIN_2 32
#define PIN_3 35

class Controller;

class AnalogManager{

public:
    AnalogManager(Model &model, Controller &controller);

    void read();

    void pollColorValues();
    void pollSmoothingValues();

    ~AnalogManager();
    
private:
    Controller *controller;
    
    Model *model;

    DeviationFilter pot1Filter;
    DeviationFilter pot2Filter;
    DeviationFilter pot3Filter;

    unsigned short raw1;
    unsigned short raw2;
    unsigned short raw3;

    void readPotentiometers();
    void readButtons();

    bool inputEligible();

    void assignBufferLens();
    void assignColors();

    void mapRaw();
};
