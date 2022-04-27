#pragma once

#include "debug.h"

#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include "persistence/EEPROMManager.h"
#include "persistence/NetInfo.h"
#include "controller/Controller.h"
#include "model/Model.h"

#define ACCESS_POINT_SSID "Led Visualiser"

class Controller;

class ServerManager : public AsyncWebServer{

public:
	ServerManager(Model &model, Controller &controller);

	Colors::RGB *clrRGB;

	void init();

	~ServerManager();

private:
    Controller *controller;
    Model *model;

	IPAddress localIP;
	IPAddress gateway;
	IPAddress subnet;

	NetInfo::info netInfo;

	//implement color picker page for both static and access point
	String staticIndex PROGMEM;
	String accessPointIndex PROGMEM;
	bool *fftMode;

	void initAccessPoint();

	//static webserver
	//void handleHomePageStatic(AsyncWebServerRequest *request);
	void handleReceivedColors(AsyncWebServerRequest *request);
	void handleFftPressed(AsyncWebServerRequest *request);

	//access point
    void handleHomePageAccessPoint(AsyncWebServerRequest *request);
    void handleReceivedCredentials(AsyncWebServerRequest *request);
};
