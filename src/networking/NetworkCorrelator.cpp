#include "networking/NetworkCorrelator.h"

NetworkCorrelator::NetworkCorrelator(Colors::RGB &clrRGB, bool &fftMode){

    this->apManager = new APManager();
    this->server = new ServerManager(clrRGB, fftMode);
}

NetworkCorrelator::~NetworkCorrelator(){
    
}