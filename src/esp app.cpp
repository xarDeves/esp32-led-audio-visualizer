#include <Arduino.h>
#include "colorUtils/ColorModes.h"
#include "colorUtils/Colors.h"
#include "engine/Engine.h"
#include "ledIO/LedStripManager.h"
#include "networking/ServerManager.h"

#define COLOR_MODE RGB

LedStripManager *ledStripManager;
ServerManager *server;
Engine *engine;

Colors::ABSTRACT clrAbstract;
Colors::RGB clrRGB;

bool fftMode = true;

void setup(){

	Serial.begin(115200);

	engine = new Engine(ColorModes::COLOR_MODE, clrRGB, clrAbstract);
	ledStripManager = new LedStripManager();
	server = new ServerManager(clrRGB, fftMode);

	server->init();
}

void loop() {
	
	//read analog inputs (free core ?)
	if (fftMode)engine->executeCycle();
	ledStripManager->emitToLedStrip(clrRGB);
}