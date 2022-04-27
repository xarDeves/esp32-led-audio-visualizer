#include "debug.h"

#include <Arduino.h>
#include "controller/Controller.h"


Controller controller;

void setup(){

	#ifdef DEBUG_APP
		Serial.begin(115200);
	#endif

	controller.init();
}

void loop() {
    
    controller.run();
}
