//
//
// criar ping no remoto
// separar get de post para o cliente não ficar recebendo a pagina
// 


void client_info() {
int valueInt = server.arg("POST_clearIdServer").toInt();
  if(valueInt >= qtdLuz){

    webSocket.broadcastTXT(build_payload(socket_payload, 3, idClient[valueInt], gpioLuz[valueInt], 0, 0),7);  

    nomeClient[valueInt] = "";
    idClient[valueInt] = 0;
    idLuz[valueInt] = 0;
    gpioLuz[valueInt] = 0;
    nomeLuz[valueInt] = "";
     
  } else {
    Serial.println("POST_clearIdServer == 0");
    Serial.println(valueInt);
  }
  
  Serial.println("[HTTP_C] Entrou na funcao client_info()");
  TelnetClient.println("[HTTP_C] Entrou na funcao client_info()");
  String value;
  String buf = "";
  buf += "<!doctype html>\r\n";
  buf += "<html>\r\n";
  buf += "<head>\r\n";
// buf += "<head><meta http-equiv=\"refresh\" content=\"8;URL=http://"+MEUIP+":82\"></head>\n";

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
  buf += "</style>\r\n";
// ####################################################
  
  buf += "</head>\r\n";
  buf += "<body bgcolor=\"ADD8E6\">\r\n";
  buf += "<center>\r\n";

  buf += "<h3> Client Status</h3>\r\n";



if(server.arg("POST_idLuz") != ""){


  POST_nomeClient = String(server.arg("POST_nomeClient"));
  POST_idClient = server.arg("POST_idClient").toInt();
  POST_idLuz = server.arg("POST_idLuz").toInt();
  POST_idServer = server.arg("POST_idServer").toInt();
  POST_gpioLuz = server.arg("POST_gpioLuz").toInt();
  POST_nomeLuz = String(server.arg("POST_nomeLuz"));

}

value= String(POST_nomeLuz);
  buf += "<p>POST_nomeLuz = "+value+"</p>\r\n";

value= String(POST_idLuz);
  buf += "<p>POST_idLuz = "+value+"</p>\r\n";
  
value= String(POST_gpioLuz);
  buf += "<p>POST_gpioLuz = "+value+"</p>\r\n";
  
value= String(POST_nomeClient);
  buf += "<p>POST_nomeClient = "+value+"</p>\r\n";

value= String(POST_idClient);
  buf += "<p>POST_idClient = "+value+"</p>\r\n";
 
value= String(POST_idServer);
  buf += "<p>POST_idServer = "+value+"</p>\r\n";


  buf += "<BR><BR>\r\n";
  buf += "<hr align=\"center\" width=\"400\" size=\"3\" color=black>\r\n";
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

  for(int p=0; p<=12; p++){
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
        buf += "<td><button type=\"submit\">Clear</button></form></td>\r\n";
        buf += "</tr>\r\n";
      }
      
    }
  }

  buf += "</table>\r\n";


  buf += "</body>\r\n";
  buf += "</html>\r\n";


  server.send(200, "text/html", buf);

Serial.print("\nantes do if POST_idServer ");
Serial.println(POST_idServer);
//////////////////// up date de base do usuario
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
          Serial.println("Enviou info fo server");
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

}



