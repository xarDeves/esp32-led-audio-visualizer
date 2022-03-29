#include <Arduino.h>
#include "colorUtils/ColorModes.h"
#include "colorUtils/Colors.h"
#include "engine/Engine.h"
#include "ledIO/LedStripManager.h"
#include "networking/ServerManager.h"
#include "analogIO/AnalogManager.h"

#define COLOR_MODE RGB

bool fftMode = false;

Colors::RGB clrRGB;

Engine engine(ColorModes::COLOR_MODE, clrRGB);
ServerManager server(clrRGB, fftMode);
AnalogManager analogManager(clrRGB, fftMode);
LedStripManager ledStripManager;

void setup(){

	Serial.begin(115200);

	server.init();
}

void loop() {

	if (fftMode)engine.executeCycle();
    //else analogManager.readAnalog();
	ledStripManager.emitToLedStrip(clrRGB);
}
