#pragma once

#include "debug.h"

#include "model/Model.h"
#include "color utils/ColorModes.h"
#include "color utils/Colors.h"
#include "audio processor/Engine.h"
#include "networking/ServerManager.h"
#include "analogIO/AnalogManager.h"
#include "ledIO/LedStripManager.h"

#define COLOR_MODE RGB

class Engine;
class ServerManager;
class AnalogManager;
class LedStripManager;

class Controller{

public:
    Controller();

    void init();
    void run();

    void FFTOn();
    void FFTOff();

    void FFTOnWifi();
    void FFTOffWifi();

    void smoothingChanged();
    void colorChanged();

    ~Controller();

private:
    Model model;

    Engine *engine;
    ServerManager *server;
    AnalogManager *analogManager;
    LedStripManager *ledStripManager;
};
