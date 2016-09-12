/*
* Codigo basico para envio de http-post com esp8266
* Basic code to send http-post with esp8266
*
* Escrito por / Write by - Paulo Eduardo
* Colaborador / colaborator - Manoel Santos
*/

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid     = "ssid_name";
const char* password = "ssid_pass";

boolean oldstatusWifi = false;
int delayversao = 0;

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


}



void loop() {
  
  HTTPClient http;
  http.begin("http://192.168.1.1");
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  http.POST("title=foo&body=bar&userId=1");
  http.writeToStream(&Serial);
  http.end();
  Serial.println("enviou o post para o server");

  delay(3000);
}
