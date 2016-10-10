/*
 * 
 * Envio de update de informações para o server
 *
 */ 
void update_inicial(){

  if(wsStatus){
    if(delayversao < millis()){
      if(wsOldStatus == false){
          IPAddress ip = WiFi.localIP();
          idClient = ip[3];             // atribui o 4 octeto do ip ao idclient
          send_info() ; // envia informaçoes das lampadas
          for(int p = 0; p < qtdLuz ; p++){
            if(digitalRead(gpioLuz[p])){              // envia status atual da lampada
              webSocket.sendTXT(build_payload(socket_payload,0, idClient, gpioLuz[p], 0, 1),7);
              } else {
              webSocket.sendTXT(build_payload(socket_payload,0, idClient, gpioLuz[p], 0, 0),7);
              }
          }
          wsOldStatus = true;
          Serial.println("[UpI] enviou up date");
      }
    }
  } else {
    wsOldStatus = false;
    delayversao = millis()+3000;
  }

//
//  if (WiFi.status() == WL_CONNECTED && pingServer){
//    if(delayversao < millis()){
//      if(oldstatusPing == false){
////      if (oldstatusWifi == false) {
//          IPAddress ip = WiFi.localIP();
//          idClient = ip[3];
//          Serial.println("[UpI] IP - ");
//          Serial.println(WiFi.localIP());
////         envia update de versao
////        webSocket.sendTXT(build_payload(socket_payload, 1, idClient, 0, versao, subversao), 7);
////        delay(5);
////         envia update dos pino utilizado
////        webSocket.sendTXT(build_payload(socket_payload, 2, idClient, 0, gpioLuz[0], 0), 7);
//          send_info() ; // envia informaçoes das lampadas
//                    
//        for(int p = 0; p < qtdLuz ; p++){
//          if(digitalRead(gpioLuz[p])){              // envia status atual da lampada
//            webSocket.sendTXT(build_payload(socket_payload,0, idClient, gpioLuz[p], 0, 1),7);
//            } else {
//            webSocket.sendTXT(build_payload(socket_payload,0, idClient, gpioLuz[p], 0, 0),7);
//            }
//        }
//
//        oldstatusPing = true;
////        oldstatusWifi = true;
//        Serial.println("[UpI] enviou up date");
//      }
//    }
//  } else {
//      oldstatusPing = false;
////      oldstatusWifi = false;
//      delayversao = millis()+2000;
////      if (divulgaAp) {
////        Serial.println("Divulgado AP");
////        WiFi.softAP("ap_teste","apteste");
////        oldstatusWifi = false;
////      }
//    }
//
}


