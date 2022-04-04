#include <Arduino.h>
#include "colorUtils/ColorModes.h"
#include "colorUtils/Colors.h"
#include "engine/Engine.h"
#include "ledIO/LedStripManager.h"
#include "networking/ServerManager.h"
#include "analogIO/AnalogManager.h"

#define COLOR_MODE RGB

bool fftMode = true;

Colors::RGB clrRGB;

Engine engine(clrRGB, ColorModes::COLOR_MODE);
ServerManager server(clrRGB, fftMode);
AnalogManager analogManager(clrRGB, fftMode);
LedStripManager ledStripManager;

void setup(){

	Serial.begin(115200);

	server.init();
}

void loop() {

    //unsigned long start = micros();

	if (fftMode)engine.executeCycle();
    else analogManager.read();
	ledStripManager.emit(clrRGB);

    //unsigned long end = micros();
    //unsigned long delta = end - start;
    //Serial.println(delta);
}
