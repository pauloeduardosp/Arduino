/*
 *Quarto
 *    V3 para ESP01
 *    V2 Rodando como server para o quarto
 *    V3 Implementação de comunicação entre os ambientes via protocolo biblioteca WebSocketsServer
 *       Utilização do WifiMAnager
 *       Exclusão da pagina HTTP para controle da luz
 *       Criação de pagina HTTP para reset do modulo
 *    V4 Implementação de abas no sketch - 22/06/2016
 *       Mudança do OTA via web arr
 *    vo
 */ // criar a rotina para ap - 
    // verificar reenvio de update qdo reconecta (reset do server)
    // 


#include <EEPROM.h>
#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
//#include <DNSServer.h> // tirar
#include <ESP8266WebServer.h>
#include <WebSocketsClient.h>
//#include <ESP8266mDNS.h> // tirar
//#include <WiFiManager.h>   // tirar       //https://github.com/tzapu/WiFiManager
//#include <WiFiUdp.h> // tirar
#include <Hash.h> // tirar
#include <ESP8266HTTPUpdateServer.h>
#include <ESP8266HTTPClient.h>
//#include <ESP8266Ping.h>

#define EEPROM_gpioLuz 1            // tamanho total 1 byte
#define EEPROM_gpioInterruptor 2    // tamanho total 1 byte
#define EEPROM_qtdLuz 3             // tamanho total 1
#define EEPROM_idLuz0 4             // tamanho total 1
#define EEPROM_idLuz1 5             // tamanho total 1
#define EEPROM_idLuz2 6             // tamanho total 1
#define EEPROM_idLuz3 7             // tamanho total 1
#define EEPROM_gpioLuz0 8           // tamanho total 1
#define EEPROM_gpioLuz1 9           // tamanho total 1
#define EEPROM_gpioLuz2 10          // tamanho total 1
#define EEPROM_gpioLuz3 11          // tamanho total 1
#define EEPROM_tipoInterruptor0 12   // tamanho total 1
#define EEPROM_tipoInterruptor1 13   // tamanho total 1
#define EEPROM_tipoInterruptor2 14   // tamanho total 1
#define EEPROM_tipoInterruptor3 15   // tamanho total 1
#define EEPROM_gpioInterruptor0 16   // tamanho total 1
#define EEPROM_gpioInterruptor1 17   // tamanho total 1
#define EEPROM_gpioInterruptor2 18   // tamanho total 1
#define EEPROM_gpioInterruptor3 19   // tamanho total 1
#define EEPROM_idServer0 20            // tamanho total 1 byte
#define EEPROM_idServer1 21            // tamanho total 1 byte
#define EEPROM_idServer2 22            // tamanho total 1 byte
#define EEPROM_idServer3 23            // tamanho total 1 byte


#define EEPROM_nomeLuz0 40          // tamanho total 20
#define EEPROM_nomeLuz1 60          // tamanho total 20
#define EEPROM_nomeLuz2 80          // tamanho total 20
#define EEPROM_nomeLuz3 100          // tamanho total 20
#define EEPROM_nomeDevice 120       // tamanho total 20



void http_reset(void);
//void verificacao_status_lampada(void);
//void update_inicial(void);
//void telnet(void);

int versao = 4;
int subversao = 6;

int gpioLuz[5] = {0};                //TX GPIO01     aba mudanca_interruptor, rst, update_inicial, verificacao_status_lampada, http_config
int gpioInterruptor[5] = {2};        //RX GPI03      aba mudanca_interruptor, http_config

String nomeDevice = "Device";
String nomeLuz[5] = {"Luz 1", "Luz 2","Luz 3","Luz 4"};

//############################################
//        Variaveis novas

//int POST_qtdLuz;
boolean divulgaAp = true;  // aba update_inicial
boolean wsStatus = false;
boolean wsOldStatus = false;
unsigned int now;

//############################################


boolean lastStatusInt[5];          // aba mudanca_interruptor
int delayinterruptor;           // aba mudanca_interruptor
boolean lastStatusLampada[5];      // aba verificaca0_status_lampada


boolean oldstatusWifi = false;  // aba update_inicial


int delayversao = 0;            // aba update_inicial

int idClient = 0;               //4 octeto do ip, definido na aba update_inicial, verificacao_status_lampada

int idLuz[5];                      //aba http_config
int tipoInterruptor[5] = {1,1,1,1};             //aba http_config
          // 1 para paralelo
          // 2 para ligado ao gpio
int qtdLuz = 1;                 //aba http_config


int idServer[4] = {0,0,0,0}; // um para cada luz   aba http_config

WebSocketsClient webSocket;

ESP8266WebServer server(82);
ESP8266HTTPUpdateServer httpUpdater;

extern "C" {
#include "user_interface.h"
}

uint8_t *socket_payload;

const uint16_t aport = 23;        //monitoria telnet standard port
WiFiServer TelnetServer(aport);   //monitoria telnet
WiFiClient TelnetClient;          //monitoria telnet


IPAddress ipServer(192,168,1,38);     // casa
//IPAddress ipServer(192,168,1,41);     // casa SERVER varanda
//IPAddress ipServer(192,168,240,134);  //telefonica


void setup() {
  Serial.begin(74880);            // Inicial Serial

  EEPROM.begin(512);              // inicial EEPROM

  loadConfig();                   // faz load das configuaçoes gravadas na eeprom para as variaveis

  TelnetServer.begin();           //monitoria via telnet
  TelnetServer.setNoDelay(true);  //monitoria via telnet

  wifi_station_set_hostname("Quarto1");

  httpUpdater.setup(&server);
  server.on("/reset",http_reset);                     // h_r
  server.on("/config", HTTP_GET, http_config);        //pagina http de confiugaracao do modulo - aba http_config
  server.on("/config", HTTP_POST, http_config_post);  //pagina http de confiugaracao do modulo - aba http_config

  server.begin();


  for(int p = 0; p < qtdLuz; p++){
    pinMode(gpioLuz[p], OUTPUT);
    pinMode(gpioInterruptor[p], INPUT);
  }




  WiFi.begin("anonymous2", "manuela.");
//  WiFi.begin("RemoteControl1", "remotecontrol");

for(int x=0; x<=10; x++){
  Serial.print(".");
  delay(1000);
   if (WiFi.status() == WL_CONNECTED){
    break;
   }
}



  String value = ipServer.toString();
  webSocket.begin(value, 81); 


  webSocket.onEvent(webSocketEvent);
  socket_payload = (uint8_t*) calloc(5, sizeof(uint8_t));
}


void loop() {
  webSocket.loop();               // referente ao websocket
  mudanca_interruptor();          // monitora o status do interruptor - aba mudança_interruptor
  server.handleClient();      // referente a funçao server.on
  verificacao_status_lampada();   // monitora o status da lampada - aba verificacao_status_lampada
  update_inicial();               // envia update inicial do modulo - aba update_inicial
  telnet();                       // monitoria via telnet - aba telnet

//
// if (WiFi.status() == WL_CONNECTED){
//    if(oldstatusWifi == false){
//      Serial.println("");
//      Serial.println(WiFi.localIP().toString());
//      TelnetClient.println("");
//      TelnetClient.println(WiFi.localIP().toString());
//      oldstatusWifi = true;
////      IPAddress ip = WiFi.localIP();
////      idClient = ip[3];
////      Serial.print("idClient ");
////      Serial.println(idClient);
//    }
//  } else if (delayversao < millis()) {
//    oldstatusWifi = false;
//    delayversao = millis()+1000;
//    Serial.print(".");
//  }



}
