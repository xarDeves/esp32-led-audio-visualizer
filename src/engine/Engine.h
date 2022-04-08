#pragma once

#include "arduinoFFT.h"
#include "persistence/EngineInfo.h"
#include "persistence/EEPROMManager.h"
#include "model/Model.h"
#include "Smoother.h"
#include "colorUtils/ColorConvertions.h"
#include "colorUtils/Colors.h"
#include "colorUtils/ColorModes.h"
#include "controller/Controller.h"

// FFT parameters
// Must be a power of 2
#define SAMPLES 512
// Hz, must be 40000 or less due to ADC conversion time. Determines maximum frequency that can be analysed by the FFT Fmax=sampleF/2.
#define SAMPLING_FREQ 40000
#define AUDIO_IN_PIN 34

class Controller;

class Engine{

public:
    Engine(Model &model, ColorModes mode, Controller &controller);

	void executeCycle();
	void setMode(ColorModes mode);
    void computeDeviders();
    void modifySmoothers();

private:
    Controller *controller;
    Model *model;
	arduinoFFT *FFT;

    Colors::ABSTRACT clrAbstract;

    Smoother rSmoother;
    Smoother gSmoother;
    Smoother bSmoother;

    unsigned int samplingPeriodUs;
	unsigned long newTime;

	double vReal[SAMPLES];
	double vImag[SAMPLES];

	float lowDevider;
	float midDevider;
	float highDevider;

	void readAudioData();
	void executeFFT();
	void (Engine::*processAudioData)();
	inline double normalize(int _start, int _end, float tMin, float tMax, float devider);

	void normalizeForHSX();
	void normalizeForLAB();
	void toRGB();
	void toHSV();
	void toHSL();
	void toLAB();
};
