#include "Engine.h"

Engine::Engine(Model &model, ColorModes mode, Controller &controller) :
bandA(model.engineInfo.lowStart, model.engineInfo.lowEnd, model.engineInfo.rSmoothingLen, model.engineInfo.noise, vReal), 
bandB(model.engineInfo.midStart, model.engineInfo.midEnd, model.engineInfo.gSmoothingLen, model.engineInfo.noise, vReal), 
bandC(model.engineInfo.highStart, model.engineInfo.highEnd, model.engineInfo.bSmoothingLen, model.engineInfo.noise, vReal){

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

	model->clrRGB.r = map(bandA.sumBand(), model->engineInfo.noise, model->engineInfo.rMax, 0 , 255);
	model->clrRGB.g = map(bandB.sumBand(), model->engineInfo.noise, model->engineInfo.rMax, 0 , 255);
	model->clrRGB.b = map(bandC.sumBand(), model->engineInfo.noise, model->engineInfo.rMax, 0 , 255);
}

void Engine::toHSL() {
	
	mapHSX();
	ColorConvertions::HSLtoRGB(clrAbstract, model->clrRGB);
}

void Engine::toHSV() {
	
	mapHSX();
	ColorConvertions::HSVtoRGB(clrAbstract, model->clrRGB);
}

void Engine::toLAB() {

	clrAbstract.a = map(bandA.sumBand(), model->engineInfo.noise, model->engineInfo.rMax, 0.0f, 100.0f);
	clrAbstract.b = map(bandB.sumBand(), model->engineInfo.noise, model->engineInfo.rMax, -100.0f, 100.0f);
	clrAbstract.c = map(bandC.sumBand(), model->engineInfo.noise, model->engineInfo.rMax, -100.0f, 100.0f);	
	ColorConvertions::LABtoRGB(clrAbstract, model->clrRGB);
}

void Engine::mapHSX(){

	clrAbstract.a = map(bandA.sumBand(), model->engineInfo.noise, model->engineInfo.rMax, 0.0f, 360.0f);
	clrAbstract.b = map(bandB.sumBand(), model->engineInfo.noise, model->engineInfo.rMax, 0.0f, 1.0f);
	clrAbstract.c = map(bandC.sumBand(), model->engineInfo.noise, model->engineInfo.rMax, 0.0f, 1.0f);
}

Engine::~Engine(){}
