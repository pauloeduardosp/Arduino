/*
 * 
 * Pagina HTTP de controle
 *  
 */

void pagina_http() {
//  Serial.println("[HTTP] Entrou na funcao pagina_http()");
//  TelnetClient.println("[HTTP] Entrou na funcao pagina_http()");

  qtdClient = qtdClient + qtdLuz;                    // soma 1 na variavel qtdClient para incluir o server
  String imgStatusLuz;
  String buf = "";



    if(server.arg("cmd_post")=="Client"){
      int x = server.arg("nClient").toInt();
      if( x < qtdLuz){
        digitalWrite(gpioLuz[x],!digitalRead(gpioLuz[x]));
        Serial.printf("[pagina_http] Acionamento gpio %d\n", x);
        Serial.printf("[pagina_http] gpioLuz[%d] - %d\n", x, gpioLuz[x]);
        TelnetClient.printf("[pagina_http] Acionamento gpio %d\n", x);
        TelnetClient.printf("[pagina_http] gpioLuz[%d] - %d\n", x, gpioLuz[x]);
      } else {
        webSocket.broadcastTXT(build_payload(socket_payload, 0, idClient[x], gpioLuz[x], 0, 3),7);       
        Serial.println("[pagina_http] Envio de websocket");
        Serial.printf("[pagina_http] Control\t0\n Client\t%d\n GPIO\t%d\n Mode\t0\n State\t3\n",idClient[x], gpioLuz[x]);
        TelnetClient.println("[pagina_http] Envio de websocket");
        TelnetClient.printf("[pagina_http] Control\t0\n Client\t%d\n GPIO\t%d\n Mode\t0\n State\t3\n",idClient[x], gpioLuz[x]);
      }

    }

//    Verifica estatus da lampada 
  for(int p = 0; p < qtdLuz;  p++){
    switch(tipoInterruptor[p]){
      case 1:   //  Paralelo
        if(digitalRead(gpioInterruptor[p])) {
          imgStatusClient[p] = 1;
        } else {
          imgStatusClient[p] = 0;
        }    
      break;
      
      case 2: //    Ligado ao GPIO
        if(digitalRead(gpioLuz[p])) {
          imgStatusClient[p] = 1;
        } else {
          imgStatusClient[p] = 0;
        }    
      
      break;
    }
  }    
//    //Verifica estatus da lampada 
//  for(int p = 0; p < qtdLuz;  p++){
//    if(digitalRead(gpioLuz[p])) {
//      imgStatusClient[p] = 1;
//    } else {
//      imgStatusClient[p] = 0;
//    }    
//  }


//  String MEUIP = WiFi.localIP().toString();
  if (server.arg("POST_teste")=="ajax_switch")  {


  buf += "<TABLE BORDER=0 align='middle'>\r\n";
//    Serial.println("######### recebeu atualização do ajax");
  
    //criação das lampadas
    byte qtdClientP = qtdClient;
    buf += "<TR>\r\n";

    byte qtdClientHttp = 3; // variavel de quantidade de clientes por linha na pagina http
    
    for(int p = 0, contador = 0; p < qtdClientP; p++){

     if(contador == qtdClientHttp){
        buf += "</TR>\r\n";
        buf += "<TR>\r\n";
        qtdClientHttp += 3;
      }
      if(nomeClient[p]!= ""){
        contador++;
        if(imgStatusClient[p]) {
          imgStatusLuz = imgLedOn;
        } else {
          imgStatusLuz = imgLedOff;
        }
        
        buf += "<TD WIDTH=150 align='middle'>\r\n";
        
        // img lampada
        buf += "<p><img width=\"46\" height=\"75\" src=\""+imgStatusLuz+"\"></p>\r\n";

        // botoes
        String ClientX = "Client";
        String strgP = String(p);    // converter p em string na variavel strgP
        ClientX += p;

        buf += "<form action='/' method='post'>\r\n";
        buf += "<input type='hidden' name=cmd_post value=Client /></p>\r\n";
        buf += "<input type='hidden' name=nClient value="+strgP+" /></p>\r\n";  //envia o numero do cliente no post http
        buf += "<button type=submit style=\"width:85px;\" value=cmd_post>"+nomeLuz[p]+"</button>\r\n";
        buf += "</form> <br/>\r\n";
        buf += "</td>\r\n";
        
      }  else {
        qtdClientP ++;
      }
      
    }
    buf += "</TR>\r\n";
  
    buf += "</table>\r\n"; 



    
    server.send(200, "text/html", buf);  
    

  } else {

  // Cabeçalho http padrão
    buf += "<!DOCTYPE html>\r\n";;
    buf += "<html>\r\n";
    buf += "<head>\r\n";
  //  buf += "<head><meta http-equiv=\"refresh\" content=\"1;URL=http://pauloeduardosp.no-ip.org:82\"></head>\n";
  //  buf += "<head><meta http-equiv=\"refresh\" content=\"10;URL=http://"+MEUIP+":82\"></head>\n";
    buf += "<title>Domotica</title>\r\n";
    buf += "<meta name=\"viewport\" content=\"width=320\">\r\n";
    buf += "<meta name=\"viewport\" content=\"width=device-width\">\r\n";
    buf += "<meta charset=\"utf-8\">\r\n";
    buf += "<meta name=\"viewport\" content=\"initial-scale=1.0, user-scalable=no\">\r\n";
  
  //############################################
  // script
      
      buf += "<script>\r\n";
      buf += "function GetSwitchState() {\r\n";
      buf += "    nocache = \"&nocache=\"\ + Math.random() * 1000000;\r\n";
      buf += "    var request = new XMLHttpRequest();\r\n";
      buf += "    request.onreadystatechange = function() {\r\n";
      buf += "        if (this.readyState == 4) {\r\n";
      buf += "            if (this.status == 200) {\r\n";
      buf += "                if (this.responseText != null) {\r\n";
      buf += "                    document.getElementById(\"switch_txt\")\.innerHTML = this.responseText;\r\n";
      buf += "                }\r\n";
      buf += "            }\r\n";
      buf += "        }\r\n";
      buf += "    }\r\n";
//      buf += "    request.open(\"POST\", \"teste_2\", true);\r\n";
      buf += "    request.open(\"POST\", \"\", true);\r\n";

      buf += "    request.send(\"POST_teste=ajax_switch\");\r\n";
      buf += "    setTimeout('GetSwitchState()', 1000);\r\n";
     
      buf += "}\r\n";
      buf += "</script>\r\n";
  // fim script
  // ####################################################
  // Style do botão clear
    buf += "<style>\r\n";
    buf += "button{\r\n";
    buf += "      cursor:pointer;\r\n";
    buf += "      border:0;border-radius:0.5rem;\r\n";
    buf += "      line-height:1.3rem;\r\n";
    buf += "      font-size:0.8rem;\r\n";
    buf += "      width:4.0rem;\r\n";
  //  buf += "      font-weight: bold;\r\n";
    buf += "    }\r\n";
    buf += "</style>\r\n";
  // ####################################################  
    
    buf += "</head>\r\n";
    buf += "<body bgcolor=\"ADD8E6\" onload=\"GetSwitchState()\">\r\n";
    buf += "<center>\r\n";
          
    buf += "<h3> Web Server Luz</h3>\r\n";

    buf +="<div id=\"switch_txt\">\r\n";
    buf += "</div>\r\n";     
   
    buf += "</center>\r\n";
    buf += "</body>\r\n";
    buf += "</html>\r\n";
            
    server.send(200, "text/html", buf);  
    }
  
  qtdClient = qtdClient - qtdLuz;  


}


