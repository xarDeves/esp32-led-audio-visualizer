#pragma once

#include "arduinoFFT.h"
#include "colorUtils/Colors.h"
#include "colorUtils/ColorConvertions.h"
#include "colorUtils/ColorModes.h"

// FFT parameters
// Must be a power of 2
#define SAMPLES 512
// Hz, must be 40000 or less due to ADC conversion time. Determines maximum frequency that can be analysed by the FFT Fmax=sampleF/2.
#define SAMPLING_FREQ 40000
#define AUDIO_IN_PIN 34
#define NOISE 600.0f

// for normalizer
#define rMin NOISE
#define rMax 200000.0f

// for 512 samples (initial limits)
#define LOW_START 2
#define LOW_END 5

#define MID_START 5
#define MID_END 68

#define HIGH_START 68
#define HIGH_END 255

/*#define LOW_START 2
#define LOW_END 6

#define MID_START 6
#define MID_END 65

#define HIGH_START 65
#define HIGH_END 255*/

class Engine{

public:
	Engine(ColorModes mode, Colors::RGB &clrRGB);

	void executeCycle();
	void setMode(ColorModes mode);

private:
	arduinoFFT *FFT;

	void (Engine::*processAudioData)();

	Colors::ABSTRACT clrAbstract;
	Colors::RGB *clrRGB;

	float lowDevider;
	float midDevider;
	float highDevider;

	unsigned int samplingPeriodUs;
	unsigned long newTime;

	double vReal[SAMPLES];
	double vImag[SAMPLES];

	void readAudioData();
	void executeFFT();
	inline double normalize(int _start, int _end, float tMin, float tMax, float devider);

	void normalizeForHSX();
	void normalizeForLAB();
	void toRGB();
	void toHSV();
	void toHSL();
	void toLAB();
};
