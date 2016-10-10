/*
 * 
 * manipulação da eeprom
 *  
 */    
 
void saveConfig() {
  Serial.println("[EEPROM] Entrou na funcao saveConfig()");
  TelnetClient.println("[EEPROM] Entrou na funcao saveConfig()");

  if(EEPROM.read(EEPROM_luz1)!=luz1){                   //valida se houve alteração na variavel antes de gravar 
    Serial.printf("[EEPROM] Atualizando luz1 na eeprom para %d\n",luz1);
    TelnetClient.printf("[EEPROM] Atualizando luz1 na eeprom para %d\n",luz1);
    EEPROM.write(EEPROM_luz1, luz1);                    // grava variavel luz na eeprom
  }

  if(EEPROM.read(EEPROM_interruptor)!=interruptor){     //valida se houve alteração na variavel antes de gravar 
    Serial.printf("[EEPROM] Atualizando interruptor na eeprom para %d\n",interruptor);
    TelnetClient.printf("[EEPROM] Atualizando interruptor na eeprom para %d\n",interruptor);
    EEPROM.write(EEPROM_interruptor, interruptor);      // grava variavel interruptor na eeprom
  }

  if(EEPROM.read(EEPROM_qtdClient)!=qtdClient){         //valida se houve alteração na variavel antes de gravar 
    Serial.printf("[EEPROM] Atualizando qtdClient na eeprom para %d\n",qtdClient);
    TelnetClient.printf("[EEPROM] Atualizando qtdClient na eeprom para %d\n",qtdClient);
    EEPROM.write(EEPROM_qtdClient, qtdClient);          // grava variavel qtdCliente na eeprom, subrai um pois a variavel sobre incremento no setup
  }

  struct temp{                                          // gera variavel temp para validar dados da 
    char ssid[30]; 
    char password[20];
  } temp;
  
  for(unsigned int p=0; p <=  sizeof(wifi); p++){   
    *((char*)&temp + p) = EEPROM.read(EEPROM_wifi + p);   // grava dados do wifi na variavel temp
  }



  if( (String(temp.ssid) != String(wifi.ssid)) ||
      (String(temp.password) != String(wifi.password))) {             // valida se houve alteração na variavel wifi antes de gravar 
    Serial.printf("[EEPROM] Atualizando wifi.ssid na eeprom para "); 
    Serial.println(String(wifi.ssid));
    Serial.printf("[EEPROM] Atualizando wifi.password na eeprom para "); 
    Serial.println(String(wifi.password));
    TelnetClient.printf("[EEPROM] Atualizando wifi ssid na eeprom para "); 
    TelnetClient.println(String(wifi.ssid));
    TelnetClient.printf("[EEPROM] Atualizando wifi.password na eeprom para "); 
    TelnetClient.println(String(wifi.password));
    for(unsigned int p=0; p <=  sizeof(wifi); p++){
      EEPROM.write(EEPROM_wifi + p, *((char*)&wifi + p)); // grava dados da variavel wifi.ssid na eeprom
    }    
  } 

 
  EEPROM.commit();

}



void loadConfig(){
  Serial.println("[EEPROM] Entrou na funcao loadConfig()");
  TelnetClient.println("[EEPROM] Entrou na funcao loadConfig()");

  if(EEPROM.read(EEPROM_luz1) != 255){                  // verifica se a eprom é diferente de 255
    luz1 = EEPROM.read(EEPROM_luz1);                    // le variavel da eeprom
  }

  if(EEPROM.read(EEPROM_interruptor) != 255){           // verifica se a eprom é diferente de 255
    interruptor = EEPROM.read(EEPROM_interruptor);      // le variavel da eeprom
  }

  if(EEPROM.read(EEPROM_qtdClient) != 255){             // verifica se a eprom é diferente de 255
    qtdClient = EEPROM.read(EEPROM_qtdClient);          // le variavel da eeprom
  }

  if((EEPROM.read(EEPROM_wifi) != 255) && (EEPROM.read(EEPROM_wifi+1) != 255)){     // verifica se a eprom é diferente de 255
    for(unsigned int p=0; p <=  sizeof(wifi); p++){
      *((char*)&wifi + p) = EEPROM.read(EEPROM_wifi + p);                           // le variavel da eeprom
    }
  }

}

