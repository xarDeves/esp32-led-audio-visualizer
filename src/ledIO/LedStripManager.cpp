#include "LedStripManager.h"

LedStripManager::LedStripManager(Controller &controller){
    
    this->controller = &controller;

    ledcSetup(R_CH, FREQ, RESOLUTION);
    ledcSetup(G_CH, FREQ, RESOLUTION);
    ledcSetup(B_CH, FREQ, RESOLUTION);

    ledcAttachPin(R_PIN, R_CH);
    ledcAttachPin(G_PIN, G_CH);
    ledcAttachPin(B_PIN, B_CH);
}

void LedStripManager::emit(Colors::RGB& color) {

    ledcWrite(R_CH, color.r);
    ledcWrite(G_CH, color.g);
    ledcWrite(B_CH, color.b);
}

void LedStripManager::emitNoise(){

}
