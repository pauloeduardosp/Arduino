/*
 *Varanda V4 para ESP01
 *    V2  Rodando como server para o quarto
 *    V3  Programado de forma modular
 *    V4  Implementação de comunicação entre os ambientes via protocolo biblioteca WebSocketsServer
 *       Utilização do WifiManager
 *    V5 Implementação de abas no sketch - 03/07/2016
 *       Mudança do OTA via web
 *
 *    WiFi.softAPdisconnect(true);
 *    desconectar o wifiap
 *
 *    WiFi.softAP(APssid, APpassword);
 *    reconectar o wiwi ap
 *
 */

// mudar variavel luz e clientPinLuz para gpioLuz
// mudar varivavel interruptor para gpioInterruptor
// arrumar a pagina config post


#include <EEPROM.h>
#include <ESP8266WiFi.h>
//#include <DNSServer.h>  //
#include <ESP8266WebServer.h>
#include <WebSocketsServer.h>
//#include <ESP8266mDNS.h>  //
//#include <WiFiManager.h>  //
//#include <WiFiUdp.h>   //
#include <Hash.h>   //
#include <ESP8266HTTPUpdateServer.h>

void http(void);
void mudanca_interruptor(void);
void http_reset(void);
void telnet(void);
void webSoket(void);

#define EEPROM_luz1 1         // tamanho total 1 byte
#define EEPROM_interruptor 2  // tamanho total 1 byte
#define EEPROM_qtdClient 3    // tamanho total 1 byte
#define EEPROM_wifi 20        // tamanho total 50 bytes=> 30 p/ ssid e 20 p/ password

//String testenull;
String post_teste1;
String post_teste2;
//int verLocal = 5;               // versao do server
//int subLocal = 0;               // subversao do server


////////////////////////////////////// novas variaveis /////////////////////
String nomeLuz[20] = {"teste1", "teste2"};
int idLuz[20] = {10, 11};
int gpioLuz[20] = {0, 0};
int idDevice[20]  = {30};
int idClient[20]  = {40};               //aba C_Status
int tipoInterruptor[5] = {1,1,1,1};  
int gpioInterruptor[20] = {2, 2};

String POST_nomeLuz;
int POST_idLuz;
int POST_gpioLuz;
String POST_nomeClient;
int POST_idClient;
int POST_idServer;

int qtdLuz = 1;

String nomeDevice = "Device";

boolean teste;

///////////////////////////////// fim novas variaveis /////////////////////

int qtdClient;              // quandidade de clientes remotos  // verificar excluir

int luz1 = 0;                   //TX GPIO01
int interruptor = 2;            //RX GPIO03

String nomeClient[20] = {"Varanda" , "Varanda"};;          //aba http

int verClient[20];              //aba http e WebSocket
int subClient[20];              //aba http e WebSocket

boolean lastStatusInt[20];          // aba mudanca_interruptor
int delayinterruptor;           // aba mudanca_interruptor

boolean oldstatusWifi = false;  // loop
int delayversao = 0;            // loop

int clientPinLuz[30];            //aba webSocket
boolean imgStatusClient[30];     //aba webSocket

String imgLedOn = "http://200.148.220.249/dashboard/Lightbulb-On.png";   // endereço da img lampada acessa
String imgLedOff = "http://200.148.220.249/dashboard/Lightbulb-Off.png"; // endereço da img lampada apagada

//10x16
//String imgLedOff = "data:image/png;base64,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";

//20x36
//String imgLedOn = "data:image/png;base64,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";


ESP8266WebServer server(82);
ESP8266HTTPUpdateServer httpUpdater;

WebSocketsServer webSocket = WebSocketsServer(81);

struct wifi{
  char ssid[30] = "anonymous2";
  char password[20] = "manuela.";
} wifi;

const char *APssid = "RemoteControl1";
const char *APpassword = "remotecontrol";

extern "C" {
#include "user_interface.h"
}

uint8_t *socket_payload;

const uint16_t aport = 23;        //monitoria telnet standard port
WiFiServer TelnetServer(aport);   //monitoria telnet
WiFiClient TelnetClient;          //monitoria telnet


void setup() {

  Serial.begin(74880);            // Inicial Serial

  EEPROM.begin(512);              // inicial EEPROM

  loadConfig();                   // faz load das configuaçoes gravadas na eeprom para as variaveis

  clientPinLuz[0]= luz1;          // aloca informação do pino da luz do sever como cliente 0
  verClient[0] = 5;//verLocal;        // aloca informação da versão do sever como cliente 0
  subClient[0] = 0; //subLocal;        // aloca informação da subversão do sever como cliente 0

  TelnetServer.begin();           //monitoria via telnet
  TelnetServer.setNoDelay(true);  //monitoria via telnet

  wifi_station_set_hostname("Domotica_Server");

  httpUpdater.setup(&server);

  server.on("/",pagina_http);               //pagina http de controle - aba http
  server.on("/config", HTTP_GET, http_config);        //pagina http de confiugaracao do modulo - aba http_config
  server.on("/config", HTTP_POST, http_config_post);  //pagina http de confiugaracao do modulo - aba http_config
  server.on("/reset",http_reset);           //pagina http de reset do modulo - aba rst
  server.on("/clientinfo", HTTP_GET, client_info);
  server.on("/clientinfo", HTTP_POST, client_info);

  server.begin();

//##############################################
//ajust array
  pinMode(luz1, OUTPUT);
  pinMode(interruptor, INPUT);
  
  for(int p = 0; p < qtdLuz; p++){
    pinMode(gpioLuz[p], OUTPUT);
    pinMode(gpioInterruptor[p], INPUT);
  }
//###############################################

//  WiFiManager wifiManager;
//  wifiManager.autoConnect("ServerRemoteControl");

  WiFi.softAP(APssid, APpassword);    //inicialização do access point
  WiFi.begin(wifi.ssid, wifi.password);         //inicialização conexao wifi
//  WiFi.begin("anonymous2", "manuela.");         //inicialização conexao wifi

Serial.print("Wifi - ");
Serial.println(wifi.ssid);
Serial.print("Senha ");
Serial.println(wifi.password);

  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
  socket_payload = (uint8_t*) calloc(5, sizeof(uint8_t));

}

void loop() {
  webSocket.loop();           // referente ao websocket
  mudanca_interruptor();      // monitora o status do interruptor - aba mudança_interruptor
  server.handleClient();      // referente a funçao server.on
  telnet();                   // monitoria via telnet - aba telnet

  if (WiFi.status() == WL_CONNECTED){
    if(oldstatusWifi == false){
      Serial.println("");
      Serial.println(WiFi.localIP().toString());
      TelnetClient.println("");
      TelnetClient.println(WiFi.localIP().toString());
      oldstatusWifi = true;
    }
  } else if (delayversao < millis()) {
    oldstatusWifi = false;
    delayversao = millis()+1000;
    Serial.print(".");
  }

}
