#include "networking/ServerManager.h"

ServerManager::ServerManager(Colors::RGB& clrRGB, bool& fftMode) : AsyncWebServer(80){

	this->clrRGB = &clrRGB;
	this->fftMode = &fftMode;

	staticIndex = R"(<html>

<script src="http://code.jquery.com/jquery-1.11.0.min.js"></script>

<script>

    var xhr = new XMLHttpRequest();

    const hexToRgb = hex =>
        hex.replace(/^#?([a-f\d])([a-f\d])([a-f\d])$/i
            , (m, r, g, b) => '#' + r + r + g + g + b + b)
            .substring(1).match(/.{2}/g)
            .map(x => parseInt(x, 16))


    $(document).ready(function () {

        $("#colorPicker").change(function () {
            var picker = document.getElementById("colorPicker");

            //var rgb = hexToRgb(document.getElementById("colorPicker").value).toString();
            //console.log(rgb);
            xhr.open("POST", "colorChanged", true);

            var data = new FormData();
            data.append('r', picker.r);
            data.append('g',  picker.g);
            data.append('b',  picker.b);
            //xhr.setRequestHeader('Content-Type', "text/html");
            xhr.send(data);
        });

        $("#fftBtn").click(function () {
            xhr.open("POST", "FFTPressed", true);
            xhr.send("");
        });

    })


</script>

<!--function getData() {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function () {
            if (this.readyState == 4 && this.status == 200) {

                var rgb = hexToRgb(document.getElementById("colorPicker").value);
                console.log(rgb.toString());
            }
        };
        xhttp.open("POST", "getColor", true);
        xhttp.send();
    }

    setInterval(function () {
        getData();
    }, 0);-->
<!--$(document).ready(function () {
        $("#colorPicker").change(function () {
            var rgb = hexToRgb(document.getElementById("colorPicker").value);
            console.log(rgb.toString());
        });
    });-->

<body style="background-color:gray;">
    <input type="color" id="colorPicker">
    <button type="button" id="fftBtn">FFT</button>
</body>

</html>)";

    accessPointIndex = R"(<!DOCTYPE html>
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
                <label for="connectIP"><strong>controller's IP address</strong></label>
                <input type="text" placeholder="Enter IP address" name="ipAddr" value="192.168.2.200" required>
                <label for="gateway"><strong>controller's gateway address</strong></label>
                <input type="text" placeholder="Enter gateway address" name="ipAddr" value="192.168.2.2" required>
                <label for="gateway"><strong>controller's subnet mask</strong></label>
                <input type="text" placeholder="Enter subnet mask" name="subnetAddr" value="255.255.0.0" required>
            </div>
            <button type="submit">Save</button>
    </form>
</body>

</html>)";

}

void ServerManager::initAccessPoint() {

    Serial.println("initializing access point");

    WiFi.softAP(ACCESS_POINT_SSID);

    on("/", HTTP_GET, std::bind(&ServerManager::handleHomePageAccessPoint, this, std::placeholders::_1));
    on("/submit", HTTP_POST, std::bind(&ServerManager::handleReceivedCredentials, this, std::placeholders::_1));

    begin();

    Serial.println("access point initialized");
}

void ServerManager::init() {

    EEPROMManager::readWifiCredentials(netInfo);

    if (netInfo.ssid[0] == '\0' || netInfo.ip[0] == '\0'  || netInfo.gateway[0] == '\0' ){
        initAccessPoint();
        return;
    }

    WiFi.mode(WIFI_STA);

    localIP.fromString(netInfo.ip);
    gateway.fromString(netInfo.gateway);
    subnet.fromString(netInfo.subnet);
	if (!WiFi.config(localIP, gateway, subnet)) {
		Serial.println("STA Failed to configure");
	}   

	WiFi.begin(netInfo.ssid, netInfo.pass);

    //10 secs
    const long interval = 10000;
    unsigned long previousMillis = 0;
    unsigned long currentMillis = millis();
    previousMillis = currentMillis;

    Serial.println("attempting to connect to: " + localIP.toString());

    while(WiFi.status() != WL_CONNECTED) {

        currentMillis = millis();
        if (currentMillis - previousMillis >= interval) {

            Serial.println("Failed to connect.");
            WiFi.disconnect();
            initAccessPoint();
            return;
        }
    }

    Serial.println("");
	Serial.println("WiFi connected successfully");
	Serial.print("Got IP: ");
	Serial.println(WiFi.localIP());
    
	//on("/", HTTP_GET, std::bind(&ServerManager::handleHomePageStatic, this, std::placeholders::_1));
	on("/colorChanged", HTTP_POST, std::bind(&ServerManager::handleReceivedColors, this, std::placeholders::_1));
	on("/FFTPressed", HTTP_POST, std::bind(&ServerManager::handleFftPressed, this, std::placeholders::_1));

	begin();
	Serial.println("HTTP server started");
}

//void ServerManager::handleHomePageStatic(AsyncWebServerRequest *request){
//        request->send(200, "text/html", staticIndex);
//}

void ServerManager::handleReceivedColors(AsyncWebServerRequest *request){

	*fftMode = false;

	clrRGB->r = (unsigned char)request->getParam(0)->value().toInt();
	clrRGB->g = (unsigned char)request->getParam(1)->value().toInt();
	clrRGB->b = (unsigned char)request->getParam(2)->value().toInt();

	request->send(200, "text/html");
}

void ServerManager::handleFftPressed(AsyncWebServerRequest *request){

 	*fftMode = true;
	request->send(200, "text/html");
}

void ServerManager::handleHomePageAccessPoint(AsyncWebServerRequest *request){

    request->send(200, "text/html", accessPointIndex);
}

void ServerManager::handleReceivedCredentials(AsyncWebServerRequest *request){

    //SSID
    strcpy(netInfo.ssid, request->getParam(0)->value().c_str());
    //password
    strcpy(netInfo.pass, request->getParam(1)->value().c_str());
    //ip address
    auto ip = request->getParam(2)->value();
    strcpy(netInfo.ip, ip.c_str());
    //gateway address
    strcpy(netInfo.gateway, request->getParam(3)->value().c_str());
    //subnet mask
    strcpy(netInfo.subnet, request->getParam(4)->value().c_str());

    EEPROMManager::writeWifiCredentials(netInfo);

    request->send(200, "text/html", "<h1>Done. ESP will restart, connect to your router and go to IP address: " + ip + "</h1>");

    delay(1000);
    ESP.restart();
}

ServerManager::~ServerManager(){
    
    WiFi.disconnect();
    end();
}
