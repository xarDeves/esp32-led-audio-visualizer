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

	//if credentials != null

	if (!WiFi.config(*this->localIP, *this->gateway, *this->subnet)) {
		Serial.println("STA Failed to configure");
	}

	WiFi.begin(SSID, NULL);
	WiFi.setSleep(false);

	for (int i = 0; i < 5; i++){
		if (WiFi.status() == WL_CONNECTED) {
			Serial.println("");
			Serial.println("WiFi connected successfully");
			Serial.print("Got IP: ");
			Serial.println(WiFi.localIP());
			return true;
		}
		else{
			delay(1000);
			Serial.print(".");
		}
	}
	return false;
	
}

void ServerManager::runWebServer() {

	this->on("/", HTTP_GET, [this](AsyncWebServerRequest *request){
        request->send(200, "text/html", this->htmlIndex);
    });

	this->on("/colorChanged", HTTP_POST, [this](AsyncWebServerRequest *request){
		*this->fftMode = false;

		this->clrRGB->r = (unsigned char)request->getParam(0)->value().toInt();
		this->clrRGB->g = (unsigned char)request->getParam(1)->value().toInt();
		this->clrRGB->b = (unsigned char)request->getParam(2)->value().toInt();

        request->send(200, "text/html");
    });

	this->on("/FFTPressed", HTTP_POST, [this](AsyncWebServerRequest *request){
        *this->fftMode = true;
        request->send(200, "text/html");
    });

	/*this->on("/", [this]() {
			this->send(200, "text/html", htmlIndex);
		});

	this->on("/colorChanged", [this]() {
			//TODO fix the +=',' jesus
			String color = this->arg(0) += ',';
			unsigned char* colors = this->jsSanitiser->extractColorsFromString(color);

			this->clrRGB->r = colors[0];
			this->clrRGB->g = colors[1];
			this->clrRGB->b = colors[2];

			*this->fftMode = false;
		});

	this->on("/FFTPressed", [this]() {
			*this->fftMode = true;
		});
	*/

	this->begin();
	Serial.println("HTTP server started");
}

ServerManager::~ServerManager(){

	//this->stop();
	//this->close();

	delete this->localIP;
	delete this->gateway;
	delete this->subnet;

	//should work...
	delete this;
}