#pragma once

#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include "persistence/EEPROMManager.h"

#define SSID "Led Visualiser"

class APManager : public AsyncWebServer {

public:
    APManager();

    bool shutdown;
    void initAccessPoint();

    ~APManager();

private:
	String htmlIndex PROGMEM;

    String ssid;
    String password;

    //AsyncWebSocket* ws;

    //globalize
	IPAddress *localIP;
	IPAddress *gateway;
	IPAddress *subnet;

    void handleHomePage(AsyncWebServerRequest *request);
    void handleReceivedCredentials(AsyncWebServerRequest *request);
};