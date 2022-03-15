#include <Arduino.h>
#include "colorUtils/ColorModes.h"
#include "colorUtils/Colors.h"
#include "engine/Engine.h"
#include "ledIO/LedStripManager.h"
#include "networking/server/ServerManager.h"
#include "networking/access point/APManager.h"

#define COLOR_MODE RGB

void networkTask( void * parameter);
TaskHandle_t networkTaskHandle;

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
	ledStripManager = new LedStripManager();
	

	apManager = new APManager();
	apManager->initAccessPoint();
	for (int i = 0; i < 15; i++){
		if (apManager->shutdown) break;
		Serial.println(i);
		delay(1000);
	}
	delete apManager;

	server = new ServerManager(clrRGB, fftMode);
	if (server->connectToRouter()) server->runWebServer();
	else delete(server);

	/*
	xTaskCreatePinnedToCore(
      networkTask,
      "Task1", 
      100000, 
      NULL,  
      0,  
      &networkTaskHandle, 
      0); 
	*/

}

void networkTask( void * parameter) {

	apManager = new APManager();
	apManager->initAccessPoint();
	for (int i = 0; i < 15; i++){
		if (apManager->shutdown) break;
		Serial.println(i);
		delay(1000);
	}
	delete apManager;

	server = new ServerManager(clrRGB, fftMode);
	if (server->connectToRouter()) server->runWebServer();
	else delete(server);
}

void loop() {
	//read analog inputs (free core ?)
	if (fftMode)engine->executeCycle();
	ledStripManager->emitToLedStrip(clrRGB);
}