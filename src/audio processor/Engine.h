#pragma once

#include "persistence/EngineInfo.h"
#include "model/Model.h"
#include "Band.h"
#include "color utils/ColorConvertions.h"
#include "color utils/Colors.h"
#include "color utils/ColorModes.h"
#include "controller/Controller.h"
#include "Sampler.h"

class Controller;

class Engine : private Sampler{

public:
    Engine(Model &model, ColorModes mode, Controller &controller);

	void executeCycle();
    void modifySmoothers();
	void setMode(ColorModes mode);

    ~Engine();

private:
    Model *model;
    Controller *controller;

    Colors::ABSTRACT clrAbstract;

	Band bandA;
	Band bandB;
	Band bandC;

	void toRGB();
	void toHSV();
	void toHSL();
	void toLAB();

	void (Engine::*processAudioData)();
};