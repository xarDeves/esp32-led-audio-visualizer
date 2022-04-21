#include "Engine.h"

Engine::Engine(Model &model, ColorModes mode, Controller &controller) :
bandA(model.engineInfo.lowStart, model.engineInfo.lowEnd, model.engineInfo.rSmoothingLen, vReal), 
bandB(model.engineInfo.midStart, model.engineInfo.midEnd, model.engineInfo.gSmoothingLen, vReal), 
bandC(model.engineInfo.highStart, model.engineInfo.highEnd, model.engineInfo.bSmoothingLen, vReal){

    this->controller = &controller;
    this->model = &model;

	setMode(mode);
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

void Engine::modifySmoothers(){

    bandA.adjustSmoothing(model->engineInfo.rSmoothingLen);
    bandB.adjustSmoothing(model->engineInfo.gSmoothingLen);
    bandC.adjustSmoothing(model->engineInfo.bSmoothingLen);
}

void Engine::toRGB() {

    model->clrRGB.r = bandA.renderRGB();
    model->clrRGB.g = bandB.renderRGB();
    model->clrRGB.b = bandC.renderRGB();
}

void Engine::toHSL() {
	
	//clrAbstract.a = normalize(model->engineInfo.lowStart, model->engineInfo.lowEnd, 0.0f, 360.0f, lowDevider);
	//clrAbstract.b = normalize(model->engineInfo.midStart, model->engineInfo.midEnd, 0.0f, 1.0f, midDevider);
	//clrAbstract.c = normalize(model->engineInfo.highStart, model->engineInfo.highEnd, 0.0f, 1.0f, highDevider);
	
	ColorConvertions::HSLtoRGB(clrAbstract, model->clrRGB);
}

void Engine::toHSV() {
	
	//clrAbstract.a = normalize(model->engineInfo.lowStart, model->engineInfo.lowEnd, 0.0f, 360.0f, lowDevider);
	//clrAbstract.b = normalize(model->engineInfo.midStart, model->engineInfo.midEnd, 0.0f, 1.0f, midDevider);
	//clrAbstract.c = normalize(model->engineInfo.highStart, model->engineInfo.highEnd, 0.0f, 1.0f, highDevider);
	ColorConvertions::HSVtoRGB(clrAbstract, model->clrRGB);
}

void Engine::toLAB() {
	
	//clrAbstract.a = normalize(model->engineInfo.lowStart, model->engineInfo.lowEnd, 0.0f, 100.0f, lowDevider);
	//clrAbstract.b = normalize(model->engineInfo.midStart, model->engineInfo.midEnd, -100.0f, 100.0f, midDevider);
	//clrAbstract.c = normalize(model->engineInfo.highStart, model->engineInfo.highEnd, -100.0f, 100.0f, highDevider);

	ColorConvertions::LABtoRGB(clrAbstract, model->clrRGB);
}

Engine::~Engine(){}
