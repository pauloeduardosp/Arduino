//
//
//
//
// 


void client_info() {


  Serial.println("[HTTP_C] Entrou na funcao client_info()");
  TelnetClient.println("[HTTP_C] Entrou na funcao client_info()");
  
//  int valueInt = server.arg("POST_clearIdServer").toInt();
//  if(valueInt >= qtdLuz){
//    Serial.printf("[HTTP_C] Enviou clear do idserver para o client %d\n",idClient[valueInt]);
//    webSocket.broadcastTXT(build_payload(socket_payload, 3, idClient[valueInt], gpioLuz[valueInt], 0, 0),7);  
//
//    nomeClient[valueInt] = "";
//    idClient[valueInt] = 0;
//    idLuz[valueInt] = 0;
//    gpioLuz[valueInt] = 0;
//    nomeLuz[valueInt] = "";
//     
//  } //else {
//    Serial.println("POST_clearIdServer == 0");
//    Serial.println(valueInt);
//  }

//##########################################################################################
// dados de data
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
  
// fim dados de data
//##########################################################################################
  

  String value;
  String buf = "";
  buf += "<!doctype html>\r\n";
  buf += "<html>\r\n";
  buf += "<head>\r\n";
  String MEUIP = WiFi.localIP().toString();
  buf += "<head><meta http-equiv=\"refresh\" content=\"10;URL=http://"+MEUIP+":82/clientinfo\"></head>\n";

  buf += "<title>Domotica Client Status</title>\r\n";
  buf += "<meta name=\"viewport\" content=\"width=320\">\r\n";
  buf += "<meta name=\"viewport\" content=\"width=device-width\">\r\n";
  buf += "<meta charset=\"utf-8\">\r\n";
  buf += "<meta name=\"viewport\" content=\"initial-scale=1.0, user-scalable=no\">\r\n";

// ####################################################
// Style do botão clear
  buf += "<style>\r\n";
  buf += "button{\r\n";
  buf += "      cursor:pointer;\r\n";
  buf += "      border:0;border-radius:0.5rem;\r\n";
  buf += "      line-height:1.3rem;\r\n";
  buf += "      font-size:0.8rem;\r\n";
  buf += "      width:4.0rem;\r\n";
  buf += "      font-weight: bold;\r\n";
  buf += "    }\r\n";
//  buf += "</style>\r\n";

  buf += "button.red{\r\n";
  buf += "      cursor:pointer;\r\n";
  buf += "      border:0;border-radius:0.5rem;\r\n";
  buf += "      line-height:1.3rem;\r\n";
  buf += "      font-size:0.8rem;\r\n";
  buf += "      width:4.0rem;\r\n";
  buf += "      font-weight: bold;\r\n";
  buf += "      background-color: rgb(255, 130, 130);\r\n";
  buf += "    }\r\n";
  buf += "</style>\r\n";
  
// ####################################################
  
  buf += "</head>\r\n";
  buf += "<body bgcolor=\"ADD8E6\">\r\n";
  buf += "<center>\r\n";

//  buf += "<h3> Client Status</h3>\r\n";
//
//
//
//  if(server.arg("POST_idLuz") != ""){
//  
//  
//    POST_nomeClient = String(server.arg("POST_nomeClient"));
//    POST_idClient = server.arg("POST_idClient").toInt();
//    POST_idLuz = server.arg("POST_idLuz").toInt();
//    POST_idServer = server.arg("POST_idServer").toInt();
//    POST_gpioLuz = server.arg("POST_gpioLuz").toInt();
//    POST_nomeLuz = String(server.arg("POST_nomeLuz"));
//  
//  }
//
//
//  value= String(POST_nomeLuz);
//  buf += "<p>POST_nomeLuz = "+value+"</p>\r\n";
//
//  value= String(POST_idLuz);
//  buf += "<p>POST_idLuz = "+value+"</p>\r\n";
//  
//  value= String(POST_gpioLuz);
//  buf += "<p>POST_gpioLuz = "+value+"</p>\r\n";
//  
//  value= String(POST_nomeClient);
//  buf += "<p>POST_nomeClient = "+value+"</p>\r\n";
//
//  value= String(POST_idClient);
//  buf += "<p>POST_idClient = "+value+"</p>\r\n";
// 
//  value= String(POST_idServer);
//  buf += "<p>POST_idServer = "+value+"</p>\r\n";
//
//
//  buf += "<BR><BR>\r\n";
//  buf += "<hr align=\"center\" width=\"400\" size=\"3\" color=black>\r\n";
// pagina lista devices
  buf += "<h3> Lista de Clientes</h3>\r\n";
  buf += "<table width=\"600px\">\r\n";
  buf += "<tr>\r\n";
  buf += "<td>Nome Cliente</td>\r\n";
  buf += "<td>Ip Cliente</td>\r\n";
  buf += "<td>Id Luz</td>\r\n";
  buf += "<td>Nome Luz</td>\r\n";
  buf += "<td>GPIO Luz</td>\r\n";
  buf += "<td>Id Server</td>\r\n";
  buf += "<td>"/*Clear Id Server*/"</td>\r\n";
  buf += "</tr>\r\n";


  for(int p=0; p<20; p++){
    if(nomeLuz[p]!=""){
      String strgP = String(p);
      buf += "<tr>\r\n";

      value= String(nomeClient[p]);
      buf += "<td>"+value+"</td>\r\n";
      
      value= String(idClient[p]);
      buf += "<td>"+value+"</td>\r\n";

      value= String(idLuz[p]);
      buf += "<td>"+value+"</td>\r\n";

      value= String(nomeLuz[p]);
      buf += "<td>"+value+"</td>\r\n";

      value= String(gpioLuz[p]);
      buf += "<td>"+value+"</td>\r\n";

      value= String(p);
      buf += "<td>"+value+"</td>\r\n";

      if(p >= qtdLuz){
        buf += "<form method=POST>\r\n";
        buf += "<input TYPE=\"hidden\" name=POST_clearIdServer value="+value+">\r\n";
        if(clientStatus[p]){
//          buf += "<td><button type=\"submit\">Clear</button></form></td>\r\n";
        } else {
          buf += "<td><button class=\"red\" type=\"submit\">Clear</button></form></td>\r\n";
        }
        buf += "</tr>\r\n";
      }

//      if(clientStatus[p]){
//        value="ok";
//      } else {
//        value="nok";
//      }
//      buf += "<td>"+value+"</td>\r\n";
      



//  qtdClientP = qtdClient;
//  for(int p=0; p <= qtdClientP; p++){
//    if(nomeClient[p]!= ""){
//      Serial.printf("clientStatus[%d] = %s\n",p, clientStatus[p]?"true":"false"); 
//    }  else {
//      qtdClientP ++;
//    }



      
    }
  }

  buf += "</table>\r\n";


  buf += "<BR><BR>\r\n";

  //criação dos rodape
  buf += "<p align=\"center\"><font size=1>";
  for(int p=0; p < qtdClient ; p++){
    
    String strgP = String(p);    // converter p em string na variavel strgP
    String strgVer = String(verClient[p]);        
    String strgSub = String(subClient[p]);
//    buf += "Client"+strgP+" V"+strgVer+"."+strgSub+"&nbsp&nbsp&nbsp - &nbsp&nbsp&nbsp";
    buf += ""+nomeClient[p]+" V"+strgVer+"."+strgSub+"&nbsp&nbsp&nbsp - &nbsp&nbsp&nbsp";

  }
  buf += "UpTime "+strgD+"d "+strgH+":"+strgM+":"+strgS+"";

  
  buf += "</body>\r\n";
  buf += "</html>\r\n";


  server.send(200, "text/html", buf);



//////////////////// up date de base do usuario
//  if(POST_idServer != 0){
//
//    nomeClient[POST_idServer] = POST_nomeClient;
//    idClient[POST_idServer] = POST_idClient;
//    idLuz[POST_idServer] = POST_idLuz;
//    gpioLuz[POST_idServer] = POST_gpioLuz;
//    nomeLuz[POST_idServer] = POST_nomeLuz;
//    
//
//  } else {
//    for(int p=qtdLuz ; p < 20; p++){
//      if(nomeLuz[p] == ""){
//        nomeClient[p] = POST_nomeClient;
//        idClient[p] = POST_idClient;
//        idLuz[p] = POST_idLuz;
//        gpioLuz[p] = POST_gpioLuz;
//        nomeLuz[p] = POST_nomeLuz;
//
//        if(idClient[p] != 0){
//          webSocket.broadcastTXT(build_payload(socket_payload, 3, idClient[p], gpioLuz[p], p, 0),7);  
//          Serial.println("Enviou info fo server");
//        }
//        
//        break;
//
//      }
//    }
//  }
//
// 
//  POST_nomeClient =  "";
//  POST_idClient =  0;
//  POST_idLuz = 0;
//  POST_gpioLuz =  0;
//  POST_nomeLuz = "";
//  POST_idServer = 0;

// atualização da qtd de clientes remotos
//  qtdClient = qtdLuz;
  qtdClient = 0;

  for (int x = qtdLuz; x < 20; x++){
    if(nomeLuz[x] != ""){
      qtdClient++ ;
    }
  }

//###################################################
// função salvar id cliente, usado para envio de update no wakeup

  for(int x = qtdLuz, p = 0; x < 20; x++){
    for(int y = x+1; y <= 20; y++){
      if(idClient[x] != idClient[y]){
        if(y == 10){
          SALVO_idClient[p] = idClient[x];
          p++;
          
        }
      } else {
        break;
      }
    }
  }

  boolean commit = false;

  for(int x = 0, y = EEPROM_idClient0; x < 20; x++, y++){
    if(SALVO_idClient[x] != EEPROM.read(y)){
      EEPROM.write(y, SALVO_idClient[x]);
      Serial.printf("[HTTP_C] Realizado update da EEPROM_idClient%d para %d\n",x, EEPROM.read(y));
      commit = true ;
    }



//    if(SALVO_idClient[x] != 0){
//      Serial.printf("SALVO_idClient[%d] = %d\n",x, SALVO_idClient[x]);  
//    }
  
    
  }

  if(commit){
    EEPROM.commit();
    Serial.println("[HTTP_C] Realizado Commit na EEPROM");
  }




// fim função salvar id cliente
//###################################################
// função keepalive do remoto

  byte qtdClientP = qtdClient;

//qtdClientP = qtdClient;
  if(delayClientStatus <= millis()){

      qtdClientP = qtdClient;

        for(int p=0; p < qtdClientP; p++){
          if(nomeClient[p]!= ""){
            clientStatus[p] = false;
            }  else {
              qtdClientP ++;
            }
      }
    webSocket.broadcastTXT(build_payload(socket_payload, 4, 255, 0, 0, 1),7);  
    delayClientStatus = millis() + 10000;
  }

// fim função keepalive do remoto  
//###########################

}



void client_info_post(){

  Serial.println("[UpDate Server Post] Entou no update_server");
  
  String MEUIP = WiFi.localIP().toString();
      
  String buf = "";
// Cabeçalho http padrão
  buf += "<!doctype html>\r\n";
  buf += "<html>\r\n";
  buf += "<head>\r\n";
//  buf += "<head><meta http-equiv=\"refresh\" content=\"1;URL=http://pauloeduardosp.no-ip.org:82\"></head>\n";
  buf += "<head><meta http-equiv=\"refresh\" content=\"1;URL=http://"+MEUIP+":82/clientinfo\"></head>\n";
  buf += "</head>\r\n";
  buf += "</html>\r\n";
          
  server.send(200, "text/html", buf);  


////////////////// recepção de inforção pelo post
  if(server.arg("POST_idLuz") != ""){
  
  
    POST_nomeClient = String(server.arg("POST_nomeClient"));
    POST_idClient = server.arg("POST_idClient").toInt();
    POST_idLuz = server.arg("POST_idLuz").toInt();
    POST_idServer = server.arg("POST_idServer").toInt();
    POST_gpioLuz = server.arg("POST_gpioLuz").toInt();
    POST_nomeLuz = String(server.arg("POST_nomeLuz"));
  
  }

////////////////// up date de base do usuario
  if(POST_idServer != 0){

    nomeClient[POST_idServer] = POST_nomeClient;
    idClient[POST_idServer] = POST_idClient;
    idLuz[POST_idServer] = POST_idLuz;
    gpioLuz[POST_idServer] = POST_gpioLuz;
    nomeLuz[POST_idServer] = POST_nomeLuz;
    

  } else {
    for(int p=qtdLuz ; p < 20; p++){
      if(nomeLuz[p] == ""){
        nomeClient[p] = POST_nomeClient;
        idClient[p] = POST_idClient;
        idLuz[p] = POST_idLuz;
        gpioLuz[p] = POST_gpioLuz;
        nomeLuz[p] = POST_nomeLuz;

        if(idClient[p] != 0){
          webSocket.broadcastTXT(build_payload(socket_payload, 3, idClient[p], gpioLuz[p], p, 0),7);  
          Serial.println("Enviou info do server");
        }
        
        break;

      }
    }
  }

 
  POST_nomeClient =  "";
  POST_idClient =  0;
  POST_idLuz = 0;
  POST_gpioLuz =  0;
  POST_nomeLuz = "";
  POST_idServer = 0;

// atualização da qtd de clientes remotos
//  qtdClient = qtdLuz;
  qtdClient = 0;
  for (int x = qtdLuz; x < 20; x++){
    if(nomeLuz[x] != ""){
      qtdClient++ ;
    }
  }



////////////////// função de clear do id de server
  int valueInt = server.arg("POST_clearIdServer").toInt();
  if(valueInt >= qtdLuz){
    Serial.printf("[HTTP_C] Enviou clear do idserver para o client %d\n",idClient[valueInt]);
//    webSocket.broadcastTXT(build_payload(socket_payload, 3, idClient[valueInt], gpioLuz[valueInt], 0, 0),7);  

    nomeClient[valueInt] = "";
    idClient[valueInt] = 0;
    idLuz[valueInt] = 0;
    gpioLuz[valueInt] = 0;
    nomeLuz[valueInt] = "";
     
  }


}

