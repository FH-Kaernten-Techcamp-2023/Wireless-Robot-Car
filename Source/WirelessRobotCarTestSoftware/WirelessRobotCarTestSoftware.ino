#include <Arduino.h>
#include "Arduino.h"
#include <ArduinoWebsockets.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>


#include "config.h"
#include "web.h"


void setup()
{
  Serial.begin(115200);

 

// sets the pins as outputs:
    pinMode(AIN1, OUTPUT);
    pinMode(AIN2, OUTPUT);
    pinMode(BIN1, OUTPUT);
    pinMode(BIN2, OUTPUT);

    pinMode(LEDFL, OUTPUT);
    pinMode(LEDFR, OUTPUT);
    pinMode(LEDBL, OUTPUT);
    pinMode(LEDBR, OUTPUT);

    pinMode(LineFolL, INPUT);
    pinMode(LineFolM, INPUT);
    pinMode(LineFolR, INPUT);   

    pinMode(WheelEncL, INPUT); 
    pinMode(WheelEncR, INPUT); 

   ledcSetup(0, freq, resolution);
   ledcSetup(1, freq, resolution);
   ledcSetup(2, freq, resolution);
   ledcSetup(3, freq, resolution);

   ledcAttachPin(AIN1, 0);
   ledcAttachPin(AIN2, 1);
   ledcAttachPin(BIN1, 2);
   ledcAttachPin(BIN2, 3);
   char ssid[29];


   
   snprintf(ssid, 29, "FH-TechCamp-WRC-%llX", ESP.getEfuseMac());



   

  // Create AP
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  Serial.print("AP SSID: ");
  Serial.println(ssid);

  // HTTP handler assignment
  webserver.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    AsyncWebServerResponse *response = request->beginResponse_P(200, "text/html", index_html_gz, sizeof(index_html_gz));
    response->addHeader("Content-Encoding", "gzip");
    request->send(response);
  });

  // start server
  webserver.begin();
  server.listen(82);
  Serial.print("Is server live? ");
  Serial.println(server.available());
 
}
 
// handle http messages
void handle_message(WebsocketsMessage msg) {
  commaIndex = msg.data().indexOf(',');
  LValue = msg.data().substring(0, commaIndex).toInt();
  RValue = msg.data().substring(commaIndex + 1).toInt();
  if (LValue<0)
  {
    ledcWrite(0, -LValue);  
    ledcWrite(1, 0);  
  }
  else
  {
    ledcWrite(0, 0);  
    ledcWrite(1, LValue);  
  }
  if (RValue<0)
  {
    ledcWrite(2, -RValue);  
    ledcWrite(3, 0);  
  }
  else
  {
    ledcWrite(2, 0);  
    ledcWrite(3, RValue);  
  }

  digitalWrite(LEDFL, !digitalRead(LEDFL));
  digitalWrite(LEDFR, !digitalRead(LEDFR));
  digitalWrite(LEDBL, !digitalRead(LEDBL));
  digitalWrite(LEDBR, !digitalRead(LEDBR));

  Serial.print(digitalRead(WheelEncL));
  Serial.print(" ");
  Serial.print(digitalRead(WheelEncR));
  Serial.print(" ");
  Serial.print(digitalRead(LineFolL));
  Serial.print(" ");
  Serial.print(digitalRead(LineFolM));
  Serial.print(" ");
  Serial.print(digitalRead(LineFolR));
  Serial.print(" ");
  Serial.print(digitalRead(LValue));
  Serial.print(" ");
  Serial.print(digitalRead(RValue));

  Serial.println();

  //motor1.drive(LValue);
  //motor2.drive(RValue);

}
 
void loop()
{
  auto client = server.accept();
  client.onMessage(handle_message);
  while (client.available()) {
    client.poll();
  }
}
