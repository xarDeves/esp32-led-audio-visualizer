#pragma once

#include "arduinoFFT.h"
#include "persistence/EngineInfo.h"
#include "persistence/EEPROMManager.h"
#include "colorUtils/Colors.h"
#include "colorUtils/ColorConvertions.h"
#include "colorUtils/ColorModes.h"

// FFT parameters
// Must be a power of 2
#define SAMPLES 512
// Hz, must be 40000 or less due to ADC conversion time. Determines maximum frequency that can be analysed by the FFT Fmax=sampleF/2.
#define SAMPLING_FREQ 40000
#define AUDIO_IN_PIN 34

class Engine{

public:
    Engine(Colors::RGB &clrRGB, ColorModes mode);

	void executeCycle();
	void setMode(ColorModes mode);

private:
	arduinoFFT *FFT;

	Colors::ABSTRACT clrAbstract;
	Colors::RGB *clrRGB;

    EngineInfo::info engineInfo;

	void (Engine::*processAudioData)();
	inline double normalize(int _start, int _end, float tMin, float tMax, float devider);

	unsigned int samplingPeriodUs;
	unsigned long newTime;

	double vReal[SAMPLES];
	double vImag[SAMPLES];

	float lowDevider;
	float midDevider;
	float highDevider;

	void readAudioData();
	void executeFFT();

	void normalizeForHSX();
	void normalizeForLAB();
	void toRGB();
	void toHSV();
	void toHSL();
	void toLAB();

    void computeDeviders();
};
