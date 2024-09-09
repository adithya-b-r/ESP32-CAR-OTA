//OTA
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>

//SSID & Password
const char* ssid = "freedata";
const char* password = "freedata";

//Motor A
const int motorPin1 = 13;
const int motorPin2 = 12;
//Motor B
const int motorPin3 = 4;
const int motorPin4 = 27;

//HTML Begin
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>
<html>
<head>
 <title>ESP32 CAR</title>
  <style>
  .h1 {
    font-size: 100px;
    text-shadow: 5px 5px #B2B2B2;
    color: blue;
  }

  .button {
    height: 250px;
    width: 250px;
    font-size: 150px;
    font-weight: bold;
    text-align: center;
    border-radius: 60px;
    background-color: gold;
    user-select: none; //This property makes the text unselectable.
  }

  .table {
    left: 50%;
    right: 50%;
    height: 600px;
    width: 800px;
    margin-top: 15%;
    border-radius: 10px;
    #background-color: grey;
  }
  </style>
</head>
<body>
<h1 class="h1" align="center"><strong>ESP32 CAR</strong></h1>

<table align="center">
  <tr>
    <td></td>
    <td><button class="button" onmousedown="toggleCheckbox('on1');" ontouchstart="toggleCheckbox('on1');" onmouseup="toggleCheckbox('off1');" ontouchend="toggleCheckbox('off1');">&#8593;</button></td>
    <td></td>
  </tr>
  <tr>
    <td><button class="button" onmousedown="toggleCheckbox('on2');" ontouchstart="toggleCheckbox('on2');" onmouseup="toggleCheckbox('off2');" ontouchend="toggleCheckbox('off2');" style="padding-bottom: 50px;">&#8592;</button></td>
    <td></td>
    <td><button class="button" onmousedown="toggleCheckbox('on3');" ontouchstart="toggleCheckbox('on3');" onmouseup="toggleCheckbox('off3');" ontouchend="toggleCheckbox('off3');" style="padding-bottom: 50px;">&#8594;</button></td>
  </tr>
  <tr>
    <td></td>
    <td><button class="button" onmousedown="toggleCheckbox('on4');" ontouchstart="toggleCheckbox('on4');" onmouseup="toggleCheckbox('off4');" ontouchend="toggleCheckbox('off4');">&#8595;</button></td>
    <td></td>
  </tr>
</table>

<script>
   function toggleCheckbox(x) {
     var xhr = new XMLHttpRequest();
     xhr.open("GET", "/" + x, true);
     xhr.send();
   }
</script>

</body>
</html>)rawliteral";
//HTML End

AsyncWebServer server(80);

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("WiFi Failed!");
    return;
  }
  Serial.println();
  Serial.print("ESP IP Address: http://");
  Serial.println(WiFi.localIP());

  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);

  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/html", index_html);
  });

  //Button 1
  server.on("/on1", HTTP_GET, [] (AsyncWebServerRequest * request) {
    front();
    request->send(200, "text/plain", "Button 1 ON");
  });

  server.on("/off1", HTTP_GET, [] (AsyncWebServerRequest * request) {
    stopwl();
    request->send(200, "text/plain", "Button 1 OFF");
  });
  
  //Button 2
  server.on("/on2", HTTP_GET, [] (AsyncWebServerRequest * request) {
    left();
    request->send(200, "text/plain", "Button 2 ON");
  });

  server.on("/off2", HTTP_GET, [] (AsyncWebServerRequest * request) {
    stopwl();
    request->send(200, "text/plain", "Button 2 OFF");
  });

  //Button 3
  server.on("/on3", HTTP_GET, [] (AsyncWebServerRequest * request) {
    right();
    request->send(200, "text/plain", "Button 3 ON");
  });

  server.on("/off3", HTTP_GET, [] (AsyncWebServerRequest * request) {
    stopwl();
    request->send(200, "text/plain", "Button 3 OFF");
  });

  //Button 4
  server.on("/on4", HTTP_GET, [] (AsyncWebServerRequest * request) {
    back();
    request->send(200, "text/plain", "Button 4 ON");
  });

  server.on("/off4", HTTP_GET, [] (AsyncWebServerRequest * request) {
    stopwl();
    request->send(200, "text/plain", "Button 4 OFF");
  });
  
  AsyncElegantOTA.begin(&server); 
  server.onNotFound(notFound);
  server.begin();
}

void loop() {

}

void front() {
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
  delay(3);
}

void back() {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, HIGH);
  delay(3);
}

void right() {
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
  delay(3);
}

void left() {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
  delay(3);
}

void stopwl()
{
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, LOW);
    digitalWrite(motorPin3, LOW);
    digitalWrite(motorPin4, LOW);
}
