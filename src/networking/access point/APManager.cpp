#include "networking/access point/APManager.h"

// if a client disconects, terminate (?)

APManager::APManager() : AsyncWebServer(80){

    this->localIP = new IPAddress(192, 168, 2, 200);
    this->gateway = new IPAddress(192, 168, 2, 252);
    this->subnet = new IPAddress(255, 255, 0, 0);

    this->credentialsReceived = false;

    this->htmlIndex = R"(<!DOCTYPE html>
<html>

<head>
    <title>Wifi Credentials</title>
    <link href="https://fonts.googleapis.com/css?family=Roboto:300,400,500,700" rel="stylesheet">
    <style>
        html,
        body {
            display: flex;
            justify-content: center;
            font-family: Roboto, Arial, sans-serif;
            font-size: 15px;
        }

        form {
            border: 5px solid #f1f1f1;
        }

        input[type=text],
        input[type=password] {
            width: 100%;
            padding: 16px 8px;
            margin: 8px 0;
            display: inline-block;
            border: 1px solid #ccc;
            box-sizing: border-box;
        }

        button {
            background-color: #8ebf42;
            color: white;
            padding: 14px 0;
            margin: 10px 0;
            border: none;
            cursor: grabbing;
            width: 100%;
        }

        h1 {
            text-align: center;
            fone-size: 18;
        }

        button:hover {
            opacity: 0.8;
        }

        .formcontainer {
            text-align: left;
            margin: 24px 50px 12px;
        }

        .container {
            padding: 16px 0;
            text-align: left;
        }

        span.psw {
            float: right;
            padding-top: 0;
            padding-right: 15px;
        }
    </style>
</head>

<body>
    <form action="/submit" method="post">
        <h1>WiFi Credentials</h1>
        <div class="formcontainer">
            <div class="container">
                <label for="SSID"><strong>SSID (name of your wifi network)</strong></label>
                <input type="text" placeholder="Enter SSID" name="SSID" required>
                <label for="psw"><strong>Password</strong></label>
                <input type="password" placeholder="Enter Password" name="psw">
            </div>
            <button type="submit">Save</button>
    </form>
</body>

</html>)";
}

void APManager::handleHomePage(AsyncWebServerRequest *request){
    request->send(200, "text/html", this->htmlIndex);
}

void APManager::handleReceivedCredentials(AsyncWebServerRequest *request){
    //TODO refer by atr name
    //SSID
    String ssid = request->getParam(0)->value();
    //password
    String pass = request->getParam(1)->value();

    EEPROMManager::writeWifiCredentials(ssid, pass);

    request->send(200, "text/html", "<h1>Credentials saved succefully. The device will now attempt to connect tou your network. Access your led controller using 192.168.2.200 in your browser after connecting to your network</h1>");

    this->credentialsReceived = true;
    return;
}

//make ip static
void APManager::initAccessPoint(){

    WiFi.softAP(SSID);
    IPAddress IP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(IP);

    this->on("/", HTTP_GET, std::bind(&APManager::handleHomePage, this, std::placeholders::_1));
    this->on("/submit", HTTP_POST, std::bind(&APManager::handleReceivedCredentials, this, std::placeholders::_1));

    this->begin();
}

APManager::~APManager(){

    client.stop();
    this->end();
}