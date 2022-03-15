#include "networking/server/ServerManager.h"

ServerManager::ServerManager(struct Colors::RGB& clrRGB, bool& fftMode) : AsyncWebServer(80){

	this->clrRGB = &clrRGB;
	this->fftMode = &fftMode;

	this->localIP = new IPAddress(192, 168, 2, 200);
	this->gateway = new IPAddress(192, 168, 2, 252);
	this->subnet = new IPAddress(255, 255, 0, 0);

	this->htmlIndex = R"(<html>

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

}

bool ServerManager::connectToRouter() {

    WiFi.mode(WIFI_STA);

	if (!WiFi.config(*this->localIP, *this->gateway, *this->subnet)) {
		Serial.println("STA Failed to configure");
	}

    String ssid;
    String pass;

    EEPROMManager::readWifiCredentials(ssid, pass);

	WiFi.begin(ssid.c_str(), pass.c_str());
	WiFi.setSleep(false);

    //10 secs
    const long interval = 10000;
    unsigned long previousMillis = 0;
    unsigned long currentMillis = millis();
    previousMillis = currentMillis;

    while(WiFi.status() != WL_CONNECTED) {
        currentMillis = millis();
        if (currentMillis - previousMillis >= interval) {
            Serial.println("Failed to connect.");
            return false;
        }
    }

    Serial.println("");
	Serial.println("WiFi connected successfully");
	Serial.print("Got IP: ");
	Serial.println(WiFi.localIP());
    
	return true;
	
}

void ServerManager::handleHomePage(AsyncWebServerRequest *request){
        request->send(200, "text/html", this->htmlIndex);
}

void ServerManager::handleReceivedColors(AsyncWebServerRequest *request){
	*this->fftMode = false;

	this->clrRGB->r = (unsigned char)request->getParam(0)->value().toInt();
	this->clrRGB->g = (unsigned char)request->getParam(1)->value().toInt();
	this->clrRGB->b = (unsigned char)request->getParam(2)->value().toInt();

	request->send(200, "text/html");
}

void ServerManager::handleFftPressed(AsyncWebServerRequest *request){
 	*this->fftMode = true;
	request->send(200, "text/html");
}

void ServerManager::runWebServer() {

	this->on("/", HTTP_GET, std::bind(&ServerManager::handleHomePage, this, std::placeholders::_1));
	this->on("/colorChanged", HTTP_POST, std::bind(&ServerManager::handleReceivedColors, this, std::placeholders::_1));
	this->on("/FFTPressed", HTTP_POST, std::bind(&ServerManager::handleFftPressed, this, std::placeholders::_1));

	this->begin();
	Serial.println("HTTP server started");
}

ServerManager::~ServerManager(){

	delete this->localIP;
	delete this->gateway;
	delete this->subnet;

    this->end();
}