#include <Arduino.h>
#include "colorUtils/ColorModes.h"
#include "colorUtils/Colors.h"
#include "engine/Engine.h"
#include "ledIO/LedStripManager.h"
#include "networking/server/ServerManager.h"
#include "networking/access point/APManager.h"

#define COLOR_MODE RGB

void wifiAvailableLoop(void *params);

TaskHandle_t core0;

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
	//implement overloaded contstuctor with static credentials
	server = new ServerManager(clrRGB, fftMode);
	//apManager = new APManager();
	ledStripManager = new LedStripManager();

	if (server->connectToRouter()){
		server->runWebServer();
		}


	//apManager->init();

	// abstract even further
	/*if (server->connectToRouter()){
		server->runWebServer();

		xTaskCreatePinnedToCore(
			wifiAvailableLoop,
			"core0",
			2000,
			NULL,
			1,
			&core0,
			0
		);

		vTaskDelete(NULL);
	}
	else{
		delete(server);
	}*/

}

void wifiAvailableLoop(void *params){
	for(;;){
		//server->handleClient();
		//read analog inputs
		if (fftMode)engine->executeCycle();
		ledStripManager->emitToLedStrip(clrRGB);
	}

}

void loop() {
	//server->server->handleClient();
	//read analog inputs
	if (fftMode)engine->executeCycle();
	ledStripManager->emitToLedStrip(clrRGB);
}

	// unsigned long start = micros();

	// unsigned long end = micros();
	// unsigned long delta = end - start;
	// Serial.println(delta);