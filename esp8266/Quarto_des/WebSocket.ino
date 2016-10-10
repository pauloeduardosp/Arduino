 
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

  if((payload[0]==0xaa) && (payload[1]==0x00) && (payload[6]==0x55)){           // alteracao de status da luz
    Serial.printf("idClient %d\n",idClient);
    if(payload[2]=idClient){
      switch (payload[4]) {
        case 0x00:    //mode 0 - lampada on/off
          if(payload[5]==0x03){
            digitalWrite(payload[3], !digitalRead(payload[3]));
            TelnetClient.println("[WSc] chegou comando");
          }
        break;

        case 0x01:    //mode 1 - reservado para PWM
          //PWM
        break;

        default:
        break;
      }
    }
  } else if((payload[0]==0xaa) && (payload[1]==0x03) && (payload[6]==0x55)){     // informaçao de idserver
    if(payload[2]==idClient){
      for(int p = 0; p < qtdLuz; p++){
        if(gpioLuz[p] == payload[3]){
          idServer[p] = payload[4];

          //###################################################
          // grava id do server na eeprom
          for(int p = EEPROM_idServer0, x = 0; p < (EEPROM_idServer0+qtdLuz); p++, x++){
            if(EEPROM.read(p)!= idServer[x]){                                    //valida se houve alteração na variavel antes de gravar 
                Serial.printf("[EEPROM SAVE] Atualizando idServer%d na eeprom para %d\n",x, idLuz[x]);
                TelnetClient.printf("[EEPROM SAVE] Atualizando idLuz%d na eeprom para %d\n",x, idLuz[x]);
                EEPROM.write(p, idServer[x]);                                      // grava variavel idserver na eeprom
            }
          }
          EEPROM.commit();
          // fim
          //###################################################
         
          break;
        }
      }
    }
  } else {
    Serial.printf("[WSc] Invalid command\n");
  }
}


void webSocketEvent(WStype_t type, uint8_t * payload, size_t lenght) {

    switch(type) {
        case WStype_DISCONNECTED:
            Serial.printf("[WSc] Disconnected!\n");
            wsStatus = false;
            break;
        case WStype_CONNECTED:
            {
            wsStatus = true;
            Serial.printf("[WSc] Connected to url: %s\n",  payload);
            webSocket.sendTXT("Connected");
            }
            break;
        case WStype_TEXT:
            Serial.printf("\n[WSc] header: %d\n", payload[0]);
            Serial.printf("[WSc] control: %d\n", payload[1]);
            Serial.printf("[WSc] client: %d\n", payload[2]);
            Serial.printf("[WSc] gpio: %d\n", payload[3]);
            Serial.printf("[WSc] mode: %d\n", payload[4]);
            Serial.printf("[WSc] state: %d\n", payload[5]);
            Serial.printf("[WSc] footer: %d\n", payload[6]);
            Serial.printf("[WSc] get text: %s\n", payload);
            command_handle(payload);
            break;
        case WStype_BIN:
            Serial.printf("[WSc] get binary lenght: %u\n", lenght);
            hexdump(payload, lenght);
            break;
    }
}
