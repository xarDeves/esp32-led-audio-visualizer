#pragma once

#include "colorUtils/Colors.h"
#include <ESPAsyncWebServer.h>
#include <WiFi.h>
#include <vector>

#define SSID "sou klevw ta accounts"

class ServerManager : public AsyncWebServer{

public:
	ServerManager(struct Colors::RGB &clrRGB, bool &fftMode);

	Colors::RGB *clrRGB;

	bool connectToRouter();
	void runWebServer();

	~ServerManager();

private:
	IPAddress *localIP;
	IPAddress *gateway;
	IPAddress *subnet;

	String htmlIndex;
	bool *fftMode;
};