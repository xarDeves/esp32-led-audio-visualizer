#include "Sampler.h"

Sampler::Sampler() : FFT(vReal, vImag, SAMPLES, SAMPLING_FREQ){

   	samplingPeriodUs = round(1000000 * (1.0 / SAMPLING_FREQ));
}

void Sampler::readAudioData() {

	for (int i = 0; i < SAMPLES; i++) {
		newTime = micros();
		vReal[i] = analogRead(AUDIO_IN_PIN);
		vImag[i] = 0;
		while ((micros() - newTime) < samplingPeriodUs) {}
	}
}

void Sampler::executeFFT() {

	FFT.DCRemoval();
	FFT.Windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD);
	FFT.Compute(FFT_FORWARD);
	FFT.ComplexToMagnitude();
}

Sampler::~Sampler(){}
