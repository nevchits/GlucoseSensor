
int i = 0;

void setup() {
  Serial.begin(9600);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  digitalWrite(7,HIGH);

  //Serial.println("Raw Input test started");
  //Serial.println("Receiver,Photodiode");
  Serial.println("Analog,Photodiode");


}

void loop() {
  //Serial.print(digitalRead(7));
  //Serial.print(",");
  for(i=0; i<255; i++){
    analogWrite(6,i);
    delay(3);
    Serial.println(i);
    Serial.println(analogRead(A0));
  }
  
 

}
