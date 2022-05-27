#include "Wire.h"

void setup() {
  Serial.begin(9600);
  //pinMode(7,INPUT_PULLUP);
  pinMode(7,OUTPUT);
  Wire.begin();
  digitalWrite(7,HIGH);

  //Serial.println("Raw Input test started");
  //Serial.println("Receiver,Photodiode");
  Serial.println("Photodiode");


}

void loop() {
  //Serial.print(digitalRead(7));
  //Serial.print(",");
  Serial.println(analogRead(A0));
 

}
