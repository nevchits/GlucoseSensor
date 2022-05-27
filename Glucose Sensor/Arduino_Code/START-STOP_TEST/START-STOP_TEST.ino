//Start-stop Test with LED

const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  4; 

int ledState = HIGH;         // the current state of the output pin  
int buttonState = 0;         // variable for reading the pushbutton status// the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin

void setup() {
  pinMode(buttonPin,INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  Serial.println("Start-Stop Test");

}

void loop() {
   // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // turn LED on:
    digitalWrite(ledPin, HIGH);
  } else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
  }

}
