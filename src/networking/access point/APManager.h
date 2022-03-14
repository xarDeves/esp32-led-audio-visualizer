#pragma once

#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include "persistence/EEPROMManager.h"

#define SSID "Led Visualiser"

class APManager : public AsyncWebServer {

public:
    APManager();

    bool credentialsReceived;
    void initAccessPoint();

    ~APManager();

private:
	String htmlIndex;

    String ssid;
    String password;

    WiFiClient client;

	IPAddress *localIP;
	IPAddress *gateway;
	IPAddress *subnet;

    void handleHomePage(AsyncWebServerRequest *request);
    void handleReceivedCredentials(AsyncWebServerRequest *request);
};