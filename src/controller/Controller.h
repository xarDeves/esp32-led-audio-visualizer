#pragma once

#include "model/Model.h"
#include "colorUtils/ColorModes.h"
#include "colorUtils/Colors.h"
#include "engine/Engine.h"
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
