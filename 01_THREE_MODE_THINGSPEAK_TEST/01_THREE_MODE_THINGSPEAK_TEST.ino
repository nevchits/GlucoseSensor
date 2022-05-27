//Three-mode test with Thingspeak
#include <ESP8266WiFi.h>
#include "ThingSpeak.h"

//const char* ssid = "REPLACE_WITH_YOUR_SSID";   // your network SSID (name) 
//const char* password = "REPLACE_WITH_YOUR_PASSWORD";   // your network password


WiFiClient  client;

//unsigned long thingspeakChannelNumber = X;
//const char * thingspeakWriteAPIKey = "XXXXXXXXXXXXXXXXX";


//Thingspeak timer variables
unsigned long lastTime = 0;
unsigned long timerDelay = 30000;

int i = 0;

const int buttonPin = D2;     // the number of the pushbutton pin
const int ledPin =  D3;    //use 5 for PWM as well
const int IRLED = D1;
const int PHOTODIODE = D0;

const int STOP = 0;
const int RUN = 1;
const int TEST = 2;
const int MANUALTEST = 3;
const int THINGSPEAKER = 4;

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
unsigned long thingspeakBlinkInterval = 250;   //to blink every tenth of a second when recording for thingspeak

int thingspeakGlucoseValue = 0;

void setup() {
  pinMode(buttonPin,INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  pinMode(IRLED, OUTPUT);
  pinMode(PHOTODIODE,OUTPUT);
  
  Serial.begin(9600);
  //Serial.println("Start-Stop Test");
  Serial.println("Photodiode");

    // set initial LED state
  digitalWrite(ledPin, ledState);

  //Setup WiFi and Thingspeak
  
  WiFi.mode(WIFI_STA);   
  
  ThingSpeak.begin(client);  // Initialize ThingSpeak

 }

void loop() {
  if ((millis() - lastTime) > timerDelay) {
    wificonnect();
    checkModeButton();
  }

}

//--------------------------------- RUN MODE STUFF ---------------------------------------------------------------

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
      if (buttonState == LOW) {
        //ledState = !ledState;
        //cycle between the 3 running modes:
        //but fIrst, reset everything
        runningState = LOW;
        
        //increment running mode
        runMode ++;
        if (runMode > THINGSPEAKER){
          runMode = STOP;
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

  //WHY didnt I use switch case?

  if (mode == STOP){
    ledState = LOW;
    digitalWrite(IRLED,LOW);
    digitalWrite(PHOTODIODE,LOW);
    
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

  else if (mode == MANUALTEST){
    manualTest();    
  }

  else if (mode == THINGSPEAKER){

    runForThingspeak();
    if (millis() - oldRunBlinkTime > thingspeakBlinkInterval){
          ledState = !ledState;
          //reset Blink Time
          oldRunBlinkTime = millis();
        }
  }

  digitalWrite(ledPin, ledState);
  
}

void runProgram(){
  digitalWrite(PHOTODIODE,HIGH);
  digitalWrite(IRLED,HIGH);
  Serial.println(analogRead(A0));
}

void testProgram(){
    
    //we are avoiding the blocking nature of for loops, without having to break...
    digitalWrite(PHOTODIODE,HIGH);
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

void manualTest(){
  //Serial.println("MANUAL");
  ledState = HIGH;
  digitalWrite(PHOTODIODE,HIGH);
  Serial.println(analogRead(A0));
}

void runForThingspeak(){
  //record for 10 seconds, blinking faster, then aggregate and send to thingspeak:
  int runningaverage = 0;
  int runcount = 0;
  long thingspeakrecordTime = millis();

  digitalWrite(PHOTODIODE,HIGH);
  digitalWrite(IRLED,HIGH);
    
  while (millis()-thingspeakrecordTime < 10000){
    runningaverage += analogRead(A0);
    Serial.println(runningaverage);
    runcount ++;
    Serial.println(runcount);

    if (millis() - oldRunBlinkTime > thingspeakBlinkInterval){
          ledState = !ledState;
          //reset Blink Time
          oldRunBlinkTime = millis();
        }
  }
  thingspeakGlucoseValue = runningaverage/runcount;
  Serial.println("SEND...");
  thinsgpeakManager();
}

int getGlucoseValue(){
  return thingspeakGlucoseValue;
}

void calibrate(){
  
}

//--------------------------------- THINGSPEAK STUFF ---------------------------------------------------------------

void thinsgpeakManager(){
//  if ((millis() - lastTime) > timerDelay) {
//      wificonnect();
//      //int glucose = getGlucoseValue();      
//      sendToThingSpeak(getGlucoseValue());
//  }
  sendToThingSpeak(getGlucoseValue());
}

void wificonnect(){
  // Connect or reconnect to WiFi
    if(WiFi.status() != WL_CONNECTED){
      Serial.print("Connect...");
      while(WiFi.status() != WL_CONNECTED){
        WiFi.begin(ssid, password);
        Serial.print("."); 
        delay(5000);     
      } 
      Serial.println("\nConnected.");
    }
}

void sendToThingSpeak(int glucoseValue){
    // Write to ThingSpeak. There are up to 8 fields in a channel, allowing you to store up to 8 different
    // pieces of information in a channel.  Here, we write to field 1.
    int HTTPRESPONSE = ThingSpeak.writeField(thingspeakChannelNumber, 1, glucoseValue, thingspeakWriteAPIKey);

    if(HTTPRESPONSE == 200){
      Serial.println("Channel update successful.");
      ledState = LOW;
    }
    else{
      Serial.println("Problem updating channel. HTTP error code " + String(HTTPRESPONSE));
    }
}
