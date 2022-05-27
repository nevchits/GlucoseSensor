//Start-stop Test with LED

int i = 0;

const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  5;    //use 5 for PWM as well
const int IRLED = 6;

const int STOP = 0;
const int RUN = 1;
const int TEST = 2;
const int LIGHTUP = 0;
const int LIGHTDOWN = 1;

int testDirection = LIGHTUP;

int runMode = 0;
int runningState = 0;

int ledState = HIGH;         // the current state of the output pin  
int buttonState = 0;         // variable for reading the pushbutton status// the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

unsigned long oldRunBlinkTime = 0;   
unsigned long runBlinkInterval = 500;   //to blink every half second

void setup() {
  pinMode(buttonPin,INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  pinMode(IRLED, OUTPUT);
  Serial.begin(9600);
  //Serial.println("Start-Stop Test");
  Serial.println("Photodiode");

    // set initial LED state
  digitalWrite(ledPin, ledState);

}

void loop() {
  checkModeButton();

}

void checkModeButton(){
  // read the state of the switch into a local variable:
  int reading = digitalRead(buttonPin);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {
        //ledState = !ledState;
        //cycle between the 3 running modes:
        //but forst, reset everything
        runningState = LOW;
        runMode ++;
        if (runMode > 2){
          runMode = 0;
          runningState = LOW;
        }
        if (runMode == 1){
          runningState = HIGH;
          oldRunBlinkTime = millis();
        }
        else {
          runningState = LOW;
        }
        //Serial.print ("RUN MODE = ");
        //Serial.println(runMode);
        //blinkIndicator(runMode,runningState);
      }
    }
  }

  // set the LED:
  //digitalWrite(ledPin, ledState);
  blinkIndicator(runMode,runningState);

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;
}

void blinkIndicator(int mode, int runState){
  //ledStatus: is it in stop mode, run mode or test mode

  if (mode == STOP){
    ledState = LOW;
    digitalWrite(IRLED,LOW);
    
  }
  else if (mode == RUN){
     digitalWrite(IRLED,LOW);
     if (runState == HIGH){
        runProgram();
        
        //flash the RED led for as long as we're in run mode
        
        if (millis() - oldRunBlinkTime > runBlinkInterval){
          ledState = !ledState;
          //reset Blink Time
          oldRunBlinkTime = millis();
        }
        
        
    }
    
  }
  else if (mode == TEST){
    testProgram();
    ledState = LOW;
    digitalWrite(IRLED,LOW);
    
  }

  digitalWrite(ledPin, ledState);
  
}

void runProgram(){
  digitalWrite(IRLED,HIGH);
}

void testProgram(){
    
    //we are avoiding the blocking nature of for loops, without having to break...
    
    analogWrite(IRLED,i);
    analogWrite(ledPin,i);
    delay(3);
    //Serial.println(i);
    Serial.println(analogRead(A0));
    i++;
    if (i > 255){
      i = 0;
    }
}
