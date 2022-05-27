#include "Wire.h"

void setup() {
  Serial.begin(9600);
  pinMode(7,INPUT_PULLUP);
  pinMode(8,INPUT_PULLUP);
  Wire.begin();

  //Serial.println("Raw Input test started");
  Serial.println("SCL,SDA");


}

void loop() {
  Serial.print(digitalRead(7));
  Serial.print(",");
  Serial.println(digitalRead(8));
 

}
