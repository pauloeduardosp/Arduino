#define SD2 9 
#define SD3 10
#define D0   16  
#define D3  0 
#define D4  2 
#define D5  14
#define D6  12
#define D7  13
#define D8  15
#define RX  3 
#define TX  1

void setup() {
  // put your setup code here, to run once:
  Serial.begin(74880);
pinMode(SD2, INPUT_PULLUP);// trava o node mcu
pinMode(SD3, INPUT_PULLUP);// ok
pinMode(D0, INPUT_PULLUP); //internal pull up não funcina
pinMode(D3, INPUT_PULLUP); // ok
pinMode(D4, INPUT_PULLUP); // ok
pinMode(D5, INPUT_PULLUP); // ok
pinMode(D6, INPUT_PULLUP); // ok
pinMode(D7, INPUT_PULLUP); // ok
//pinMode(D8, INPUT_PULLUP); // trava
pinMode(RX, INPUT_PULLUP); // ok
//pinMode(TX, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
Serial.print(digitalRead(SD2));
Serial.print(digitalRead(SD3));
Serial.print(digitalRead( D0));
Serial.print(digitalRead( D3));
Serial.print(digitalRead( D4));
Serial.print(digitalRead( D5));
Serial.print(digitalRead( D6));
Serial.print(digitalRead( D7));
//Serial.print(digitalRead( D8));
Serial.println(digitalRead( RX));
//Serial.println(digitalRead( TX));

delay(250);
}
