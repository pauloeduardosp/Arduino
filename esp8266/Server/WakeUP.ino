/*
 * 
 *  Funão para divulgação AP
 *  Envio de wakeup  para os clientes 
 * 
 */ 

void wakeup(){


//##########################################################
//#### função parar de divulgar AP
  if(divulgaAP){
    if(millis() > 300000){
      if (WiFi.status() == WL_CONNECTED){
        WiFi.softAPdisconnect(true);
        divulgaAP = false;
        
        Serial.println("[Wifi_status] Parou de divulgar AP ");
        TelnetClient.println("[Wifi_status] Parou de divulgar AP ");
      }
    }
  }
//#### fim função parar de divulgar AP
//##########################################################

//##########################################################
//#### função envio de update de conexão para os clientes

  String value;
  if (WiFi.status() == WL_CONNECTED){
    
    String MEUIP = WiFi.localIP().toString();
    if(oldstatusWifi == false){
    
        for(int p = 0; p < qtdLuz ; p++){
          idClient[p] = MEUIP[3];
        }
        Serial.print("[wakeup] Conectado a rede ");
        Serial.println(wifi.ssid);
        Serial.print("[wakeup] Ip do modulo ");
        Serial.println(WiFi.localIP().toString());
        TelnetClient.print("[wakeup] Conectado a rede ");
        TelnetClient.println(wifi.ssid);
        TelnetClient.print("[wakeup] Ip do modulo ");
        TelnetClient.println(WiFi.localIP().toString());

      HTTPClient http;

      for(byte x = EEPROM_idClient0; x <= EEPROM_idClient19; x++){

        if(EEPROM.read(x) != 0 && EEPROM.read(x) != 255){

          IPAddress ip = WiFi.localIP();
          value = String(ip[0]);
          value += ".";
          value += String(ip[1]);
          value += ".";
          value += String(ip[2]);
          value += ".";
          value += String(EEPROM.read(x));
          
          http.begin("http://"+value+":82/update_server");
          http.addHeader("Content-Type", "application/x-www-form-urlencoded");
      
          http.POST("POST_updateServer=serverConectado");
      
          http.writeToStream(&Serial);
          http.end();    

          Serial.print("[WakeUP] Enviou informacao para o cliente ");
          Serial.println(value);
        }
      }

      oldstatusWifi = true;
    }
  } else {
    oldstatusWifi = false;
  }

//#### fim função envio de update de conexão para os clientes
//##########################################################

  
}


