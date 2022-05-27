#include "Wire.h"

void setup() {
  Serial.begin(9600);
  pinMode(D0,INPUT_PULLUP);
  pinMode(D4,INPUT_PULLUP);
  Wire.begin();

  //Serial.println("Raw Input test started");
  Serial.println("SCL,SDA");


}

void loop() {
  Serial.print(digitalRead(D0));
  Serial.print(",");
  Serial.println(digitalRead(D4));
 

}
