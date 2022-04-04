#include "LedStripManager.h"

LedStripManager::LedStripManager(){

    ledcSetup(R_CH, FREQ, RESOLUTION);
    ledcSetup(G_CH, FREQ, RESOLUTION);
    ledcSetup(B_CH, FREQ, RESOLUTION);

    ledcAttachPin(R_PIN, R_CH);
    ledcAttachPin(G_PIN, G_CH);
    ledcAttachPin(B_PIN, B_CH);
}

void LedStripManager::emit(Colors::RGB& color) {

    ledcWrite(R_CH, (int)color.r);
    ledcWrite(G_CH, (int)color.g);
    ledcWrite(B_CH, (int)color.b);
}

void LedStripManager::emitNoise(){

}
