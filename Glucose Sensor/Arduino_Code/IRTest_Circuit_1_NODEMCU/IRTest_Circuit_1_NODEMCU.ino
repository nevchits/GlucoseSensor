
int i = 0;
const int IRLED = D1;
const int PHOTODIODE = D0;

void setup() {
  Serial.begin(9600);
  pinMode(IRLED,OUTPUT);
  pinMode(PHOTODIODE,OUTPUT);
  digitalWrite(PHOTODIODE,HIGH);

  //Serial.println("Raw Input test started");
  //Serial.println("Receiver,Photodiode");
  Serial.println("Analog,Photodiode");


}

void loop() {
  //Serial.print(digitalRead(7));
  //Serial.print(",");
  for(i=0; i<255; i++){
    analogWrite(IRLED,i);
    delay(3);
    Serial.println(i);
    Serial.println(analogRead(A0));
  }
  
 

}
