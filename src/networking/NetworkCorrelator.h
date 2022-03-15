#pragma once

#include "networking/access point/APManager.h"
#include "networking/server/ServerManager.h"

class NetworkCorrelator{

public:
    NetworkCorrelator(Colors::RGB &clrRGB, bool &fftMode);

    ~NetworkCorrelator();
private:
    ServerManager *server;
    APManager *apManager;

};