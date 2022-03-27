#include <Arduino.h>
#include "colorUtils/ColorModes.h"
#include "colorUtils/Colors.h"
#include "engine/Engine.h"
#include "ledIO/LedStripManager.h"
#include "networking/ServerManager.h"
//#include "analogIO/AnalogManager.h"

#define COLOR_MODE RGB

bool fftMode = true;

Colors::RGB clrRGB;

Engine engine(ColorModes::COLOR_MODE, clrRGB);
ServerManager server(clrRGB, fftMode);
//AnalogManager analogManager(clrRGB, fftMode);
LedStripManager ledStripManager;

void setup(){

	Serial.begin(115200);

	server.init();
}

void loop() {
	
	//read analog inputs (free core ?)
	if (fftMode)engine.executeCycle();
	ledStripManager.emitToLedStrip(clrRGB);
}