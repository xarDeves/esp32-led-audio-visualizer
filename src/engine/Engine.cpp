#include "Engine.h"

Engine::Engine(Model &model, ColorModes mode, Controller &controller) :
rSmoother(model.engineInfo.rSmoothingLen), 
gSmoother(model.engineInfo.gSmoothingLen), 
bSmoother(model.engineInfo.bSmoothingLen){

	FFT = new arduinoFFT(vReal, vImag, SAMPLES, SAMPLING_FREQ);

    this->controller = &controller;
    this->model = &model;

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
    controller->colorChanged();
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

inline double Engine::normalize(int _start, int _end, float tMin, float tMax, float devider) {

	double sum = 0.0f;

	for (int i = _start; i < _end; i++) {
		if (vReal[i] > model->engineInfo.noise)
			sum += vReal[i];
	}

	return tMax * ((sum / devider) - model->engineInfo.noise) / (model->engineInfo.rMax - model->engineInfo.noise);
}

void Engine::modifySmoothers(){

    rSmoother.setLen(model->engineInfo.rSmoothingLen);
    gSmoother.setLen(model->engineInfo.gSmoothingLen);
    bSmoother.setLen(model->engineInfo.bSmoothingLen);
}

void Engine::toRGB() {

    model->clrRGB.r = normalize(model->engineInfo.lowStart, model->engineInfo.lowEnd, 0.0f, 255.0f, lowDevider);
    model->clrRGB.g = normalize(model->engineInfo.midStart, model->engineInfo.midEnd, 0.0f, 255.0f, midDevider);
    model->clrRGB.b = normalize(model->engineInfo.highStart, model->engineInfo.highEnd, 0.0f, 255.0f, highDevider);

    rSmoother.smooth(model->clrRGB.r);
    gSmoother.smooth(model->clrRGB.g); 
    bSmoother.smooth(model->clrRGB.b);
}

void Engine::toHSL() {

	normalizeForHSX();
	ColorConvertions::HSLtoRGB(clrAbstract, model->clrRGB);
}

void Engine::toLAB() {

	normalizeForLAB();
	ColorConvertions::LABtoRGB(clrAbstract, model->clrRGB);
}

void Engine::toHSV() {

	normalizeForHSX();
	ColorConvertions::HSVtoRGB(clrAbstract, model->clrRGB);
}

void Engine::normalizeForHSX() {

	clrAbstract.a = normalize(model->engineInfo.lowStart, model->engineInfo.lowEnd, 0.0f, 360.0f, lowDevider);
	clrAbstract.b = normalize(model->engineInfo.midStart, model->engineInfo.midEnd, 0.0f, 1.0f, midDevider);
	clrAbstract.c = normalize(model->engineInfo.highStart, model->engineInfo.highEnd, 0.0f, 1.0f, highDevider);
}

void Engine::normalizeForLAB() {

	clrAbstract.a = normalize(model->engineInfo.lowStart, model->engineInfo.lowEnd, 0.0f, 100.0f, lowDevider);
	clrAbstract.b = normalize(model->engineInfo.midStart, model->engineInfo.midEnd, -100.0f, 100.0f, midDevider);
	clrAbstract.c = normalize(model->engineInfo.highStart, model->engineInfo.highEnd, -100.0f, 100.0f, highDevider);

	//Serial.printf("%d - %d - %d\n", clrLAB->l, clrLAB->a, clrLAB->b);
}

void Engine::computeDeviders(){

    //EEPROMManager::readmodel->engineInfo(model->engineInfo);
    
    /*Serial.println(model->engineInfo.lowStart);
    Serial.println(model->engineInfo.lowEnd);
    Serial.println(model->engineInfo.midStart);
    Serial.println(model->engineInfo.midEnd);
    Serial.println(model->engineInfo.highStart);
    Serial.println(model->engineInfo.highEnd);*/

	lowDevider = log(model->engineInfo.lowEnd - model->engineInfo.lowStart);
	midDevider = log(model->engineInfo.midEnd - model->engineInfo.midStart);
	highDevider = log(model->engineInfo.highEnd - model->engineInfo.highStart);
}
