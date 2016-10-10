/*
 * 
 * 
 * Pagina HTTP de configuração
 *  
 */
//arrumar o config post

void http_config() {
  
  Serial.println("[HTTP_C] Entrou na funcao http_config()");
  TelnetClient.println("[HTTP_C] Entrou na funcao http_config()");
  String value;
  String valuep;
    
  String buf = "";
  
// Cabeçalho http padrão
  buf += "<!doctype html>\r\n";
  buf += "<html>\r\n";
  buf += "<head>\r\n";
//  buf += "<head><meta http-equiv=\"refresh\" content=\"1;URL=http://pauloeduardosp.no-ip.org:82\"></head>\n";

  buf += "<title>Domotica Config Server</title>\r\n";
  buf += "<meta name=\"viewport\" content=\"width=320\">\r\n";
  buf += "<meta name=\"viewport\" content=\"width=device-width\">\r\n";
  buf += "<meta charset=\"utf-8\">\r\n";
  buf += "<meta name=\"viewport\" content=\"initial-scale=1.0, user-scalable=no\">\r\n";

// ####################################################
// Style 
  buf += "<style>\r\n";
  buf += "button{\r\n";
  buf += "      cursor:pointer;\r\n";
  buf += "      border:0;border-radius:0.5rem;\r\n";
  buf += "      line-height:1.9rem;\r\n";
  buf += "      font-size:0.9rem;\r\n";
  buf += "      width:6.0rem;\r\n";
  buf += "      font-weight: bold;\r\n";
  buf += "    }\r\n";
  
  buf += "  input[type=\"number\"] {\r\n";
  buf += "   width:30px;\r\n";
  buf += "}\r\n";
  buf += "</style>\r\n";
// ####################################################
  
  buf += "</head>\r\n";
  buf += "<body bgcolor=\"ADD8E6\">\r\n";
  buf += "<font face=\"arial\" size=\"3\">\r\n";
  buf += "<center>\r\n";
  buf += "<BR>\r\n";
  buf += "<form method=POST>\r\n";
  buf += "<title>Domotica Config Server</title>\r\n";
  buf += "<h3>Configuração Server</h3>\r\n";
  
  buf += "<table>\r\n";


  if(WiFi.status() == WL_CONNECTED){
    buf += "<tr>\r\n";
    buf += "<td>Status:</td>\r\n";
    buf += "<td><b>Conectado</b></td>\r\n";
    buf += "</tr>\r\n";

    value = String(WiFi.SSID());
    buf += "<tr>\r\n";
    buf += "<td width=100px>Rede Wifi:</td>\r\n";
    buf += "<td>"+value+"</td>\r\n";
    buf += "</tr>\r\n";

    value = WiFi.localIP().toString();
    buf += "<tr>\r\n";
    buf += "<td>IP:</td>\r\n";
    buf += "<td>"+value+"</td>\r\n";
    buf += "</tr>\r\n";

  } else {
    buf += "<tr>\r\n";
    buf += "<td>Status:</td>\r\n";
    buf += "<td><b>Desconectado</b></td>\r\n";
    buf += "</tr>\r\n";
    
    value = String(wifi.ssid);
    buf += "<tr>\r\n";
    buf += "</tr>\r\n";
    buf += "</table>\r\n";
    buf += "<label>Tentando conectar a rede <b>"+value+"</b>\r\n";
  }

    
// ####################################################
// Config Cliente
//  buf += "<title>Domotica Config Cliente</title>\r\n";
//  buf += "<h3> Configuração Cliente</h3>\r\n";



  buf += "<table>\r\n";
  buf += "<BR>\r\n";
  buf += "<tr>\r\n";
  buf += "<td><label>Nome Device:</label></td>\r\n";
  value = String(nomeDevice);
  buf += "<td><input name=POST_nomeDevice type=text value=\""+value+"\" size=15></td>\r\n";
  buf += "</tr>\r\n";

  buf += "<tr>\r\n";
  buf += "<td width = 115px><label>Qtd de Luzes:</label></td>\r\n";
  buf += "<td>\r\n";


  buf += "<select name=POST_qtdLuz>\r\n";
  for(int p = 1; p <= 4; p++){
  value = String(p);
    if(p==qtdLuz){
      buf += "<option value=\""+value+"\" selected>"+value+"</option>\r\n";
    }else{
      buf += "<option value=\""+value+"\">"+value+"</option>\r\n";
    }
  }
  buf += "</select>\r\n";
  buf += "</td>\r\n";
  buf += "</table>\r\n";

  buf += "<BR>\r\n";
  buf += "<hr align=\"center\" width=\"380\" size=\"3\" color=black>\r\n";

  // ####################################################
  // Configuração Luz

  buf += "<h3> Configuração Luz</h3>\r\n";
  buf += "<table>\r\n";

  buf += "<tr align = left>\r\n";
  buf += "<td width=\"50px\"><label> &nbsp </label></td>\r\n";
  buf += "<td width=\"50px\"><label> ID: </label></td>\r\n";
  buf += "<td width=\"50px\"><label> Gpio:</label></td>\r\n";
  buf += "<td width=\"100px\"><label> Nome: </label></td>\r\n";
//  buf += "<td><label> IDServer: </label></td>\r\n";
  buf += "</tr>\r\n";

  for(int p = 0; p < qtdLuz; p++){
    buf += "<tr align=left>\r\n";
    valuep = String(p);
    buf += "<td><label> Luz "+valuep+" </label></td>\r\n";
    value = String(idLuz[p]);
    buf += "<td><input type=\"number\" name=POST_idLuz"+valuep+" type=text value="+value+"></td>\r\n";
    value = String(gpioLuz[p]);
    buf += "<td><input type=\"number\" name=POST_gpioLuz"+valuep+" type=text value="+value+"></td>\r\n";
    value = String(nomeLuz[p]);
    buf += "<td><input name=POST_nomeLuz"+valuep+" type=text value="+value+" size=\"10\"></td>\r\n";


  buf += "</tr>\r\n";
  buf += "</table>\r\n";

  buf += "<BR>\r\n";
  buf += "<hr align=\"center\" width=\"380\" size=\"3\" color=black>\r\n";

  // ####################################################
  // Configuração Interruptor

  buf += "<h3>Configuração Interruptor</h3>\r\n";
  buf += "<table>\r\n";

  buf += "<tr align = left>\r\n";
  buf += "<td width=\"100px\"><label></label></td>\r\n";
  buf += "<td width=\"120px\"><label>Tipo:</label></td>\r\n";
  buf += "<td><label>Gpio:</label></td>\r\n";
  buf += "</tr>\r\n";

  for(int p = 0; p < qtdLuz; p++){
    buf += "<tr>\r\n";
    valuep = String(p);
    buf += "<td><label> Interruptor "+valuep+"</label></td>\r\n";
    buf += "<td>\r\n";
    buf += "<select name=\"POST_tipoInterruptor"+valuep+"\">\r\n";
    if(tipoInterruptor[p] == 1){
      buf += "<option value=\"1\" selected>Paralelo</option>\r\n";
    } else {
      buf += "<option value=\"1\">Paralelo</option>\r\n";
    }

    if(tipoInterruptor[p] == 2){
      buf += "<option value=\"2\" selected>ligado no Gpio</option>\r\n";
    } else {
      buf += "<option value=\"2\">ligado no Gpio</option>\r\n";
    }

    buf += "</select>\r\n";
    buf += "</td>\r\n";


    value = String(gpioInterruptor[p]);
    buf += "<td><input type=\"number\"  name=POST_gpioInterruptor"+valuep+" type=text value="+value+"></td>\r\n";

    buf += "</tr>\r\n";
  }

  buf += "</table>\r\n";
  buf += "<BR><BR>\r\n";
  buf += "<button type=\"submit\">Salvar</button></form>\r\n";

  buf += "</center>\r\n";
  buf += "</body>\r\n";
  buf += "</html>\r\n";

  server.send(200, "text/html", buf);


}

//
//  buf += "<tr>\r\n";
//  buf += "<td><label>GPIO Luz: </label></td>\r\n";
//  value = String(luz1);
//  buf += "<td><input name=POST_luz1 type=text value="+value+"></td>\r\n";
//  buf += "</tr>\r\n";
//
//  buf += "<tr>\r\n";
//  buf += "<td><label>GPIO Interuptor: </label></td>\r\n";
//  value = String(interruptor);
//  buf += "<td><input name=POST_interruptor type=text value="+value+"></td>\r\n";
//  buf += "</tr>\r\n";
//
//  buf += "<tr>\r\n";
//  buf += "<td><label>Qtd Clientes Remotos: </label></td>\r\n";
//  value = String(qtdClient);
//  buf += "<td><input name=POST_qtdClient type=text value="+value+"></td>\r\n";
//  buf += "</tr>\r\n";
//
//  buf += "<tr>\r\n";
//  buf += "<td><label>SSID: </label></td>\r\n";
//  value = String(wifi.ssid);
//  buf += "<td><input name=txtSSID type=text value="+value+"></td>\r\n";
//  buf += "</tr>\r\n";
//
//
//  buf += "<tr>\r\n";
//  buf += "<td><label>Senha: </label></td>\r\n";
//  value = String(wifi.password);
//  buf += "<td><input type=\"password\" name=txtSenha type=text  value="+value+"></td>\r\n";
//  buf += "</tr>\r\n";
//
//  buf += "</table>\r\n";
//  
//  buf += "<p><input name=button1 type=submit value=Enviar ></p></form>\r\n";
//
//
//
//
//  buf += "</center>\r\n";
//  buf += "</body>\r\n";
//  buf += "</html>\r\n";
//          
//  server.send(200, "text/html", buf);


}



void http_config_post() {
  Serial.println("[HTTP_C] Entrou na funcao http_config_post()");
  TelnetClient.println("[HTTP_C] Entrou na funcao http_config_post()");

  String MEUIP = WiFi.localIP().toString();
  String buf = "";
  buf += "<!doctype html>\r\n";
  buf += "<html>\r\n";
  buf += "<head>\r\n";
  buf += "<head><meta http-equiv=\"refresh\" content=\"8;URL=http://"+MEUIP+":82\"></head>\n";

  buf += "<title>Domotica Config Receive</title>\r\n";
  buf += "<meta name=\"viewport\" content=\"width=320\">\r\n";
  buf += "<meta name=\"viewport\" content=\"width=device-width\">\r\n";
  buf += "<meta charset=\"utf-8\">\r\n";
  buf += "<meta name=\"viewport\" content=\"initial-scale=1.0, user-scalable=no\">\r\n";
  buf += "</head>\r\n";
  buf += "<body bgcolor=\"ADD8E6\">\r\n";
  buf += "<center>\r\n";

  buf += "<h3> Config Receive Web Server Luz</h3>\r\n";
  buf += "Dados salvo, realizando reset no modulo\r\n";

  buf += "</body>\r\n";
  buf += "</html>\r\n";

  server.send(200, "text/html", buf);

//  luz1 = server.arg("POST_luz1").toInt();
//  interruptor = server.arg("POST_interruptor").toInt();
  qtdClient = server.arg("POST_qtdClient").toInt();
  server.arg("txtSSID").toCharArray(wifi.ssid, 30);

  if(wifi.password != ""){
    server.arg("txtSenha").toCharArray(wifi.password, 20);  
  } 

  saveConfig();
  ESP.restart();


}

