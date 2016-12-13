
uint8_t * build_payload(uint8_t *payload, uint8_t control, uint8_t client, uint8_t gpio, uint8_t mode, uint8_t state){
  payload[0] = 0xaa;
  payload[1] = control;
  payload[2] = client;
  payload[3] = gpio;
  payload[4] = mode;
  payload[5] = state;
  payload[6] = 0x55;
  return payload;
}


void command_handle(uint8_t *payload) {
  if((payload[0]==0xaa) && (payload[6]==0x55)) {    //header e footer
    switch(payload[1]) {                            //control
      case  0x00:     //control 0 - atualização de status da lampada
          switch(payload[4]){
              case 0x00:    //mode 0 - lampada on/off
                  if(payload[5]==0x01){
                    imgStatusClient[payload[2]] = 1;
                  }
                  else if(payload[5]==0x00){
                    imgStatusClient[payload[2]] = 0;
                  }
                  
              break;
              case 0x01:    //mode 1 - reservado para PWM
                //PWM
              break;
              default:
              break;
          }
      break;

      case 0x01:      //control 1 - update de versão dos modulos remotos
        verClient[payload[2]]= payload[4];
        subClient[payload[2]]= payload[5];  
      break;

      case 0x02:    // control 2 - update de informação do GPIO utilizado pelos modulos remotos
        clientPinLuz[payload[2]] = payload[4];
      break;

      case 0x04:    // control 4 - keepalive
        if(payload[5] == 2){
          clientStatus[payload[4]] = true;
        }
      break;
      
      default:
      break;
      
    }

  } else {
    Serial.printf("[WSc] Invalid command\n");
    TelnetClient.printf("[WSc] Invalid command\n");
  }
}


void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t lenght) {

  switch(type) {
    case WStype_DISCONNECTED:
    Serial.printf("[WSc] [%u] Disconnected!\n", num);
    TelnetClient.printf("[WSc] [%u] Disconnected!\n", num);
    break;
    case WStype_CONNECTED:
      {
        IPAddress ip = webSocket.remoteIP(num);
        Serial.printf("[WSc] [%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);
        TelnetClient.printf("[WSc] [%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);
        webSocket.sendTXT(num, "Connected");
      }
      break;
    case WStype_TEXT:
        Serial.printf("\n[WSc] header: %d\n", payload[0]);
        TelnetClient.printf("\n[WSc] header: %d\n", payload[0]);
        Serial.printf("[WSc] control: %d\n", payload[1]);
        TelnetClient.printf("[WSc] control: %d\n", payload[1]);
        Serial.printf("[WSc] client: %d\n", payload[2]);
        TelnetClient.printf("[WSc] client: %d\n", payload[2]);

      
      if(payload[1]==0x00){             //control 0 - atualização de status da lampada
        Serial.printf("[WSc] gpio: %d\n", payload[3]);
        TelnetClient.printf("[WSc] gpio: %d\n", payload[3]);
        Serial.printf("[WSc] mode: %d\n", payload[4]);
        TelnetClient.printf("[WSc] mode: %d\n", payload[4]);
        Serial.printf("[WSc] state: %d\n", payload[5]);
        TelnetClient.printf("[WSc] state: %d\n", payload[5]);

      } else if (payload[1]==0x01){     //control 1 - update de versão dos modulos remotos
        Serial.printf("[WSc] name: %d\n", payload[3]);
        TelnetClient.printf("[WSc] name: %d\n", payload[3]);
        Serial.printf("[WSc] versao: %d\n", payload[4]);
        TelnetClient.printf("[WSc] versao: %d\n", payload[4]);
        Serial.printf("[WSc] subversao: %d\n", payload[5]);
        TelnetClient.printf("[WSc] subversao: %d\n", payload[5]);

      
      } else if (payload[1]==0x02){     // control 2 - update de informação do GPIO utilizado pelos modulos remotos
        Serial.printf("[WSc] reservado: %d\n", payload[3]);
        TelnetClient.printf("[WSc] reservado: %d\n", payload[3]);
        Serial.printf("[WSc] GPIO Client: %d\n", payload[4]);
        TelnetClient.printf("[WSc] GPIO Client: %d\n", payload[4]);
        Serial.printf("[WSc] reservado: %d\n", payload[5]);
        TelnetClient.printf("[WSc] reservado: %d\n", payload[5]);

      } else if (payload[1]==0x04){     // control 2 - update de informação do GPIO utilizado pelos modulos remotos
        Serial.printf("[WSc] reservado: %d\n", payload[3]);
        TelnetClient.printf("[WSc] reservado: %d\n", payload[3]);
        Serial.printf("[WSc] GPIO Client: %d\n", payload[4]);
        TelnetClient.printf("[WSc] GPIO Client: %d\n", payload[4]);
        Serial.printf("[WSc] reservado: %d\n", payload[5]);
        TelnetClient.printf("[WSc] reservado: %d\n", payload[5]);
      }
      
      Serial.printf("[WSc] footer: %d\n", payload[6]);
      TelnetClient.printf("[WSc] footer: %d\n", payload[6]);
      Serial.printf("[WSc] get text: %s\n", payload);
      TelnetClient.printf("[WSc] get text: %s\n", payload);
      command_handle(payload);
      break;
    case WStype_BIN:
      Serial.printf("[WSc] [%u] get binary lenght: %u\n", num, lenght);
      TelnetClient.printf("[WSc] [%u] get binary lenght: %u\n", num, lenght);
      hexdump(payload, lenght);
      break;
  }
}


