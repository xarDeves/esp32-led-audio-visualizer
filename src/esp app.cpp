#include <Arduino.h>
#include "colorUtils/ColorModes.h"
#include "colorUtils/Colors.h"
#include "engine/Engine.h"
#include "ledIO/LedStripManager.h"
#include "networking/server/ServerManager.h"
#include "networking/access point/APManager.h"

#define COLOR_MODE RGB

LedStripManager *ledStripManager;
ServerManager *server;
APManager *apManager;
Engine *engine;

Colors::ABSTRACT clrAbstract;
Colors::RGB clrRGB;

bool fftMode = true;

void setup(){

	Serial.begin(115200);

	engine = new Engine(ColorModes::COLOR_MODE, clrRGB, clrAbstract);
	apManager = new APManager();
	server = new ServerManager(clrRGB, fftMode);
	ledStripManager = new LedStripManager();

	//random exception accures, check destructors
	apManager->initAccessPoint();
	for (int i = 0; i < 15; i++){
		if (apManager->credentialsReceived) break;
		delay(1000);
	}
	delete apManager;
	if (server->connectToRouter()) server->runWebServer();
	else delete(server);
}

void loop() {
	//read analog inputs (most possibly on free core)
	if (fftMode)engine->executeCycle();
	ledStripManager->emitToLedStrip(clrRGB);
}