#pragma once

#include "colorUtils/Colors.h"
#include <ESPAsyncWebServer.h>
#include "persistence/EEPROMManager.h"
#include "networking/NetInfo.h"
#include <WiFi.h>

#define ACCESS_POINT_SSID "Led Visualiser"

class ServerManager : public AsyncWebServer{

public:
	ServerManager(struct Colors::RGB &clrRGB, bool &fftMode);

	Colors::RGB *clrRGB;

	void init();

	~ServerManager();

private:
	IPAddress *localIP;
	IPAddress *gateway;
	IPAddress *subnet;

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