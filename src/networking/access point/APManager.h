#pragma once

#include <WiFi.h>
#include <ESPAsyncWebServer.h>

#define SSID "Led Visualiser"

class APManager : public AsyncWebServer {

public:
    APManager();

    void init();

    ~APManager();

private:
	String htmlIndex;

    String ssid;
    String password;

    WiFiClient client;
    //String header;
    // make a String to hold incoming data from the client
    //String currentLine;        

	IPAddress *localIP;
	IPAddress *gateway;
	IPAddress *subnet;
};