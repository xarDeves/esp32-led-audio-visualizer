#pragma once

#include "filter/DeviationFilter.h"
#include "controller/Controller.h"
#include "devices/Potentiometer.h"
#include "model/Model.h"

#define BUFF_LEN 200
#define DEVIATION_MAX 30
#define MAP_MAX 255

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

    Potentiometer pot1;
    Potentiometer pot2;
    Potentiometer pot3;

    void readPotentiometers();
    void readButtons();

    bool inputEligible();

    void assignBufferLens();
    void assignColors();
};
