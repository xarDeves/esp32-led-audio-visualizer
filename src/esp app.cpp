#include <Arduino.h>
#include "controller/Controller.h"

Controller controller;

void setup(){

	Serial.begin(115200);

	controller.init();
}

void loop() {
    
    controller.run();
}
