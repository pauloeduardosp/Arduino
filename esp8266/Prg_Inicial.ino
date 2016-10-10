#include <Arduino.h>

/*
 *  This sketch sends data via HTTP GET requests to data.sparkfun.com service.
 *
 *  You need to get streamId and privateKey at data.sparkfun.com and paste them
 *  below. Or just customize this script to talk to other HTTP servers.
 *
 */

#include <ESP8266WiFi.h>

const char* ssid     = "anonymous2";
const char* password = "manuela.";




void setup() {
  Serial.begin(74880);
  delay(10);

  // We start by connecting to a WiFi network
  Serial.printf("\nConnecting to %s\n", ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());


    pinMode(2, OUTPUT);
    pinMode(1, OUTPUT);

    pinMode(0, OUTPUT);
    pinMode(3, OUTPUT);
}



void loop() {

if(digitalRead(3)){
  digitalWrite(1, !digitalRead(1));
  digitalWrite(2, !digitalRead(2));
}


//if(digitalRead(3)){
//  digitalWrite(2, !digitalRead(2));
//}


}


