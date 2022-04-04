#include "Engine.h"

Engine::Engine(Colors::RGB &clrRGB, ColorModes mode) {

	FFT = new arduinoFFT(vReal, vImag, SAMPLES, SAMPLING_FREQ);
	this->clrRGB = &clrRGB;
	setMode(mode);

    computeDeviders();

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
		if (vReal[i] > engineInfo.noise)
			sum += vReal[i];
	}

	return tMax * ((sum / devider) - engineInfo.noise) / (engineInfo.rMax - engineInfo.noise);
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

	FFT->DCRemoval();
	FFT->Windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD);
	FFT->Compute(FFT_FORWARD);
	FFT->ComplexToMagnitude();
}

void Engine::normalizeForHSX() {

	clrAbstract.a = normalize(engineInfo.lowStart, engineInfo.lowEnd, 0.0f, 360.0f, lowDevider);
	clrAbstract.b = normalize(engineInfo.midStart, engineInfo.midEnd, 0.0f, 1.0f, midDevider);
	clrAbstract.c = normalize(engineInfo.highStart, engineInfo.highEnd, 0.0f, 1.0f, highDevider);
}

void Engine::normalizeForLAB() {

	clrAbstract.a = normalize(engineInfo.lowStart, engineInfo.lowEnd, 0.0f, 100.0f, lowDevider);
	clrAbstract.b = normalize(engineInfo.midStart, engineInfo.midEnd, -100.0f, 100.0f, midDevider);
	clrAbstract.c = normalize(engineInfo.highStart, engineInfo.highEnd, -100.0f, 100.0f, highDevider);

	//Serial.printf("%d - %d - %d\n", clrLAB->l, clrLAB->a, clrLAB->b);
}

void Engine::toRGB() {

	clrRGB->r = normalize(engineInfo.lowStart, engineInfo.lowEnd, 0.0f, 255.0f, lowDevider);
	clrRGB->g = normalize(engineInfo.midStart, engineInfo.midEnd, 0.0f, 255.0f, midDevider);
	clrRGB->b = normalize(engineInfo.highStart, engineInfo.highEnd, 0.0f, 255.0f, highDevider);
}

void Engine::toHSL() {

	normalizeForHSX();
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

void Engine::computeDeviders(){

    //EEPROMManager::readEngineInfo(engineInfo);
    
    /*Serial.println(engineInfo.lowStart);
    Serial.println(engineInfo.lowEnd);
    Serial.println(engineInfo.midStart);
    Serial.println(engineInfo.midEnd);
    Serial.println(engineInfo.highStart);
    Serial.println(engineInfo.highEnd);*/

	lowDevider = log(engineInfo.lowEnd - engineInfo.lowStart);
	midDevider = log(engineInfo.midEnd - engineInfo.midStart);
	highDevider = log(engineInfo.highEnd - engineInfo.highStart);
}
