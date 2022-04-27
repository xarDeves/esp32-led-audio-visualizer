#pragma once

#include "debug.h"

#include "arduinoFFT.h"
// FFT parameters
// Must be a power of 2
#define SAMPLES 512
// Hz, must be 40000 or less due to ADC conversion time.
// Determines maximum frequency that can be analysed by the FFT Fmax = sample F/2.
#define SAMPLING_FREQ 40000
#define AUDIO_IN_PIN 34

class Sampler{

public:
    Sampler();

    ~Sampler();
protected:

	double vReal[SAMPLES];

	void readAudioData();
	void executeFFT();

private:
	arduinoFFT FFT;

	double vImag[SAMPLES];

	unsigned long newTime;
    unsigned int samplingPeriodUs;
};