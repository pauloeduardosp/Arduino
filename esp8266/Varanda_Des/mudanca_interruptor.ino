#include <Arduino.h>

/*
 * 
 * Verifica mudança de status do interruptor
 *     
 */

void mudanca_interruptor(){

/*
  if (digitalRead(interruptor) != lastStatusInt){
    digitalWrite(luz1, !digitalRead(luz1));
    Serial.println("mudança de status interruptor");
    delay(1500);
    lastStatusInt = digitalRead(interruptor);
  }
*/

//#####################################################
// ajuste array
//
//  if(delayinterruptor<millis()){
//    if (digitalRead(interruptor) != lastStatusInt){
//      digitalWrite(luz1, !digitalRead(luz1));
//      Serial.println("[MInt] Mudança de status interruptor");
//      TelnetClient.print("[MInt] Mudança de status interruptor - ");
//      TelnetClient.print(digitalRead(luz1));
//      TelnetClient.print(" - ");
//      TelnetClient.println(millis()/1000);
//      lastStatusInt = digitalRead(interruptor);
//      delayinterruptor=millis()+800;
//    }
//  }

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
