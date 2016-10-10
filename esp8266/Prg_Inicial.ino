#include <Arduino.h>

/*
 *  This sketch sends data via HTTP GET requests to data.sparkfun.com service.
 *
 *  You need to get streamId and privateKey at data.sparkfun.com and paste them
 *  below. Or just customize this script to talk to other HTTP servers.
 *
 */

#include <ESP8266WiFi.h>

const char* ssid     = "ssid";
const char* password = "pass";




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
    pinMode(0, OUTPUT);

}



void loop() {


//if(digitalRead(3)){
//  digitalWrite(2, !digitalRead(2));
//}


}


