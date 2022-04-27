#include "Controller.h"

Controller::Controller() {

    engine = new Engine(model, ColorModes::COLOR_MODE, *this);
    server = new ServerManager(model, *this);
    analogManager = new AnalogManager(model, *this);
    ledStripManager = new LedStripManager(*this);
}

void Controller::init(){

	server->init();
}

void Controller::run(){

    analogManager->read();
}

void Controller::FFTOn(){

    #ifdef BENCHMARK_FFT
        unsigned long start = micros();
    #endif
    
    engine->executeCycle();
    analogManager->pollSmoothingValues();

    #ifdef BENCHMARK_FFT
        unsigned long end = micros();
        unsigned long delta = end - start;
        Serial.println(delta);
    #endif

}

void Controller::FFTOff(){

    analogManager->pollColorValues();
}

void Controller::FFTOnWifi(){

    model.fftMode = true;
    FFTOn();
}

void Controller::FFTOffWifi(){

    model.fftMode = false;
    FFTOff();
}

void Controller::smoothingChanged(){

    engine->modifySmoothers();
}

void Controller::colorChanged(){

    ledStripManager->emit(model.clrRGB);
}

Controller::~Controller(){
    
    delete engine;
    delete ledStripManager;
    delete analogManager;
    delete server;
}