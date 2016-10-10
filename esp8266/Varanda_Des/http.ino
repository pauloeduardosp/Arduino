/*
 * 
 * Pagina HTTP de controle
 *  
 */

void pagina_http() {
//  Serial.println("[HTTP] Entrou na funcao pagina_http()");
//  TelnetClient.println("[HTTP] Entrou na funcao pagina_http()");

  qtdClient++;                    // soma 1 na variavel qtdClient para incluir o server
  
  String imgStatusLuz;

  int segundos =  (millis()/(1000) % 60);  
  int minutos =   (millis()/(60000) % 60);   // (millis()/(1000*60)%60
  int horas =     (millis()/(3600000) % 24);   // (millis()/(1000*60*60)%60  
  int dias =      (millis()/(86400000)  % 24);       // (milliseconds / (1000*60*60*24)) % 24);
  String strgD = String(dias);
  String strgH;
  String strgM;
  String strgS;
  
  if(horas  < 10){
    strgH = "0"+String(horas);
  } else {
    strgH = String(horas);
  }
  if(minutos <10){
    strgM = "0"+String(minutos);
  } else {
    strgM = String(minutos);
  }
  if(segundos <10){
    strgS = "0"+String(segundos);
  } else {
    strgS = String(segundos);
  }

//###################################
// ajuste array
//  if (server.hasArg("cmd_post")){
    if(server.arg("cmd_post")=="Client"){
      int x = server.arg("nClient").toInt();
      if( x < qtdLuz){
        digitalWrite(gpioLuz[x],!digitalRead(gpioLuz[1]));
        Serial.printf("Acionamento gpio %d\n", x);
        Serial.printf("gpioLuz[%d] - %d\n", x, gpioLuz[x]);
      } else {
        webSocket.broadcastTXT(build_payload(socket_payload, 0, idClient[x], gpioLuz[x], 0, 3),7);       
        Serial.println("Envio de websocket");
        Serial.printf("Control\t0\n Client\t%d\n GPIO\t%d\n Mode\t0\n State\t3\n",idClient[x], gpioLuz[x]);
      }
       
      Serial.print("post do Client ");
      Serial.println(x);
    }

//  }

//  if (server.hasArg("cmd_post"))  {
//     if((server.arg("cmd_post")=="Client") && (server.arg("nClient")=="0")) {
//      Serial.println("post do Client0");
//      digitalWrite(luz1,!digitalRead(luz1));
//    }
//     if(server.arg("cmd_post")=="Client") {
//      for(int p=1; p < qtdClient; p++){
//        String strgP = String(p);    // converter p em string na variavel strgP
//        if(server.arg("nClient")==strgP){
////          webSocket.broadcastTXT(build_payload(socket_payload, 0, p, clientPinLuz[p], 0, 3),7);
//          webSocket.broadcastTXT(build_payload(socket_payload, 0, 54, 1, 0, 3),7);
//
//          Serial.print("post do Client ");
//          Serial.print(p);
//        }
//      }
//    }
//  }
// fim ajuste array
//#####################################################

//###################################
// ajuste array
  //Verifica estatus da lampada 
//  if(digitalRead(luz1)) {
//    imgStatusClient[0] = 1;
//  } else {
//    imgStatusClient[0] = 0;
//  }

    //Verifica estatus da lampada 
  for(int p = 0; p < qtdLuz;  p++){
    if(digitalRead(gpioLuz[p])) {
      imgStatusClient[0] = 1;
    } else {
      imgStatusClient[0] = 0;
    }    
  }
// fim ajuste array
//#####################################################

  String MEUIP = WiFi.localIP().toString();
  
  String buf = "";
// Cabeçalho http padrão
  buf += "<!doctype html>\r\n";
  buf += "<html>\r\n";
  buf += "<head>\r\n";
//  buf += "<head><meta http-equiv=\"refresh\" content=\"1;URL=http://pauloeduardosp.no-ip.org:82\"></head>\n";
  buf += "<head><meta http-equiv=\"refresh\" content=\"1;URL=http://"+MEUIP+":82\"></head>\n";

  buf += "<title>Domotica</title>\r\n";
  buf += "<meta name=\"viewport\" content=\"width=320\">\r\n";
  buf += "<meta name=\"viewport\" content=\"width=device-width\">\r\n";
  buf += "<meta charset=\"utf-8\">\r\n";
  buf += "<meta name=\"viewport\" content=\"initial-scale=1.0, user-scalable=no\">\r\n";
  buf += "</head>\r\n";
  buf += "<body bgcolor=\"ADD8E6\">\r\n";
  buf += "<center>\r\n";
        
  buf += "<h3> Web Server Luz</h3>\r\n";

  buf += "<TABLE BORDER=0 align='middle'>\r\n";

  //criação das lampadas
  buf += "<TR>\r\n";
  for(int p=0; p < qtdClient ; p++){
    if(imgStatusClient[p] == 1){
      imgStatusLuz = imgLedOn;
    } else {
      imgStatusLuz = imgLedOff;
    }
    buf += "<TD align='middle'><p><img width=\"46\" height=\"75\" src=\""+imgStatusLuz+"\"></p></TD>\r\n";
  }
  buf += "</TR>\r\n";

  //criação dos botoes
  buf += "<TR>\r\n";
  for(int p=0; p < qtdClient ; p++){
    String ClientX = "Client";
    String strgP = String(p);    // converter p em string na variavel strgP
    ClientX += p;
    //post do http
    buf += "<TD WIDTH=150 align='middle'><form action='/' method='post'>\r\n";
    buf += "<input type='hidden' name=cmd_post value=Client /></p>\r\n";
    buf += "<input type='hidden' name=nClient value="+strgP+" /></p>\r\n";  //envia o numero do cliente no post http
    buf += "<button type=submit style=\"width:85px;\" value=cmd_post>"+nomeClient[p]+"</button>\r\n";
    buf += "</form> <br/></td>\r\n"; 
  }
  buf += "</table>\r\n";  
  buf += "</center>\r\n";

  //criação dos rodape
  buf += "<p align=\"center\"><font size=1>";
  for(int p=0; p < qtdClient ; p++){
    String strgP = String(p);    // converter p em string na variavel strgP
    String strgVer = String(verClient[p]);        
    String strgSub = String(subClient[p]);
    buf += "Client"+strgP+" V"+strgVer+"."+strgSub+"&nbsp&nbsp&nbsp - &nbsp&nbsp&nbsp";
  }
  buf += ""+strgD+"d "+strgH+":"+strgM+":"+strgS+"";
  buf += "</font></p>\r\n";

        
  buf += "</body>\r\n";
  buf += "</html>\r\n";
          
  server.send(200, "text/html", buf);  

  qtdClient--;


}


