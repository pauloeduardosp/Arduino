/*
 *  
 * Verifica mudança de status do interruptor
 *     
 */
void mudanca_interruptor(){
//
//  if (digitalRead(gpioInterruptor) != lastStatusInt){
////  if(delayinterruptor<millis()){
////   if (digitalRead(gpioInterruptor) != lastStatusInt){
//      digitalWrite(gpioLuz, !digitalRead(gpioLuz));
//      Serial.println("[MI] mudança de status interruptor");
//      TelnetClient.print("mudança de status interruptor - ");
//      TelnetClient.print(digitalRead(gpioLuz));
//      TelnetClient.print(" - ");
//      TelnetClient.println(millis()/1000);
//      lastStatusInt = digitalRead(gpioInterruptor);
//      delayinterruptor=millis()+800;
//      delay(750);
//      }
//   }
////}



  for(int p = 0; p < qtdLuz; p++){
    if (digitalRead(gpioInterruptor[p]) != lastStatusInt[p]){
  //  if(delayinterruptor<millis()){
  //   if (digitalRead(gpioInterruptor[p]) != lastStatusInt[p]){
        digitalWrite(gpioLuz[p], !digitalRead(gpioLuz[p]));
        Serial.println("[MI] mudança de status interruptor");
        TelnetClient.print("mudança de status interruptor - ");
        lastStatusInt[p] = digitalRead(gpioInterruptor[p]);
        delayinterruptor=millis()+800;
        delay(750);
        }
     }
//  }
}
