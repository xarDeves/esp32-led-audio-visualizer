#pragma once

#include "debug.h"

#include <esp32-hal-ledc.h>
#include "color utils/Colors.h"
#include "controller/Controller.h"

// PWM properties
#define FREQ 1500
#define RESOLUTION 8
#define R_CH 0
#define G_CH 1
#define B_CH 2

// signal out pins
#define R_PIN 27
#define G_PIN 26
#define B_PIN 25

class Controller;

class LedStripManager{

public:
	LedStripManager(Controller &controller);

	void emit(Colors::RGB &color);
	void emitNoise();

private:
    Controller *controller;
};
