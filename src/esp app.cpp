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
	server = new ServerManager(clrRGB, fftMode);
	//apManager = new APManager();
	ledStripManager = new LedStripManager();

	//apManager->init();

	// abstract even further
	if (server->connectToRouter()){
		server->runWebServer();
	}
	/*else{
		delete(server);
	}*/

}


void loop() {
	//read analog inputs
	if (fftMode)engine->executeCycle();
	ledStripManager->emitToLedStrip(clrRGB);
}