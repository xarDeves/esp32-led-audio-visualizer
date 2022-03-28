#include "Engine.h"

Engine::Engine(ColorModes mode, Colors::RGB &clrRGB) {

	this->FFT = new arduinoFFT(vReal, vImag, SAMPLES, SAMPLING_FREQ);
	this->clrRGB = &clrRGB;
	this->setMode(mode);

	lowDevider = log(LOW_END - LOW_START);
	midDevider = log(MID_END - MID_START);
	highDevider = log(HIGH_END - HIGH_START);

	samplingPeriodUs = round(1000000 * (1.0 / SAMPLING_FREQ));

}

void Engine::setMode(ColorModes mode){

	switch (mode) {
	case RGB:
		processAudioData = &Engine::toRGB;
		break;
	case HSV:
		processAudioData = &Engine::toHSV;
		break;
	case HSL:
		processAudioData = &Engine::toHSL;
		break;
	case LAB:
		processAudioData = &Engine::toLAB;
		break;
	}
}

void Engine::executeCycle() {

	readAudioData();
	executeFFT();
	(this->*processAudioData)();
}

inline double Engine::normalize(int _start, int _end, float tMin, float tMax, float devider) {

	double sum = 0.0f;

	for (int i = _start; i < _end; i++) {
		if (vReal[i] > NOISE)
			sum += vReal[i];
	}

	return tMax * ((sum / devider) - rMin) / (rMax - rMin);
}

void Engine::readAudioData() {

	for (int i = 0; i < SAMPLES; i++) {
		newTime = micros();
		vReal[i] = analogRead(AUDIO_IN_PIN);
		vImag[i] = 0;
		while ((micros() - newTime) < samplingPeriodUs) {}
	}
}

void Engine::executeFFT() {

	this->FFT->DCRemoval();
	this->FFT->Windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD);
	this->FFT->Compute(FFT_FORWARD);
	this->FFT->ComplexToMagnitude();
}

void Engine::normalizeForHSX() {

	clrAbstract.a = normalize(LOW_START, LOW_END, 0.0f, 360.0f, lowDevider);
	clrAbstract.b = normalize(MID_START, MID_END, 0.0f, 1.0f, midDevider);
	clrAbstract.c = normalize(HIGH_START, HIGH_END, 0.0f, 1.0f, highDevider);
}

void Engine::normalizeForLAB() {

	clrAbstract.a = normalize(LOW_START, LOW_END, 0.0f, 100.0f, lowDevider);
	clrAbstract.b = normalize(MID_START, MID_END, -100.0f, 100.0f, midDevider);
	clrAbstract.c = normalize(HIGH_START, HIGH_END, -100.0f, 100.0f, highDevider);

	//Serial.printf("%d - %d - %d\n", clrLAB->l, clrLAB->a, clrLAB->b);
}

void Engine::toRGB() {

	clrRGB->r = normalize(LOW_START, LOW_END, 0.0f, 255.0f, lowDevider);
	clrRGB->g = normalize(MID_START, MID_END, 0.0f, 255.0f, midDevider);
	clrRGB->b = normalize(HIGH_START, HIGH_END, 0.0f, 255.0f, highDevider);

	//weighted distribution
	//clrRGB->r = (clrRGB->r * 0.70f + clrRGB->g * 0.15f + clrRGB->b * 0.15f);
	//clrRGB->g = (clrRGB->r * 0.25f + clrRGB->g * 0.5f + clrRGB->b * 0.25f);
	//clrRGB->b = (clrRGB->r * 0.20f + clrRGB->g * 0.4f + clrRGB->b * 0.4f);
}

void Engine::toHSL() {

	normalizeForHSX();

	//weighted distribution
	//clrHSX->h = (clrHSX->h * 0.70f + clrHSX->s * 0.15f + clrHSX->x * 0.15f);
	//clrHSX->s = (clrHSX->h * 0.25f + clrHSX->s * 0.5f + clrHSX->x * 0.25f);
	//clrHSX->x = (clrHSX->h * 0.25f + clrHSX->s * 0.4f + clrHSX->x * 0.4f);

	ColorConvertions::HSLtoRGB(clrAbstract, *clrRGB);
}

void Engine::toLAB() {

	normalizeForLAB();
	ColorConvertions::LABtoRGB(clrAbstract, *clrRGB);
}

void Engine::toHSV() {

	normalizeForHSX();
	ColorConvertions::HSVtoRGB(clrAbstract, *clrRGB);
}
