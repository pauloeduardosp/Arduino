 void send_info(){
// 

  for(int p = 0; p < qtdLuz; p++){
    String value = ipServer.toString();
    HTTPClient http;
    http.begin("http://"+value+":82/clientinfo");
    // http.begin("http://200.148.220.249/teste%20post.html");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    String srtg_nomeDevice = String(nomeDevice);
    String srtg_idClient = String(idClient);
    String srtg_idLuz = String(idLuz[p]);
    String srtg_idServer = String(idServer[p]);
    String srtg_gpioLuz = String(gpioLuz[p]);
    String srtg_nomeLuz = String(nomeLuz[p]);
    String srtg_envioClient = "envioclient";

    http.POST("POST_nomeClient="+srtg_nomeDevice+"&POST_idClient="+srtg_idClient+"&POST_idLuz="+srtg_idLuz+"&POST_idServer="+srtg_idServer+"&POST_gpioLuz="+srtg_gpioLuz+"&POST_nomeLuz="+srtg_nomeLuz+"&POST_envioClient="+srtg_envioClient+"");

    http.writeToStream(&Serial);
    http.end();
  }

 }
