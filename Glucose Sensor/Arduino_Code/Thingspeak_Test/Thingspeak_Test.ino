/*
  Adapted from WriteSingleField Example from ThingSpeak Library (Mathworks)
  and Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp8266-nodemcu-thingspeak-publish-arduino/
*/

#include <ESP8266WiFi.h>
#include "ThingSpeak.h"

//const char* ssid = "REPLACE_WITH_YOUR_SSID";   // your network SSID (name) 
//const char* password = "REPLACE_WITH_YOUR_PASSWORD";   // your network password

WiFiClient  client;

unsigned long myChannelNumber = 4;
const char * myWriteAPIKey = "7UNDHSR2H0I27ZV5";

long randNumber;


// Timer variables
unsigned long lastTime = 0;
unsigned long timerDelay = 30000;

// Variable to hold temperature readings
float glucose;

void setup() {
  Serial.begin(9600);  //Initialize serial
  Serial.println("Random Numbers to Thingspeak");
  
  WiFi.mode(WIFI_STA);   
  
  ThingSpeak.begin(client);  // Initialize ThingSpeak

  //generate random number:
  // if analog input pin 0 is unconnected, random analog
  // noise will cause the call to randomSeed() to generate
  // different seed numbers each time the sketch runs.
  // randomSeed() will then shuffle the random function.
  randomSeed(analogRead(0));
}

void loop() {
  if ((millis() - lastTime) > timerDelay) {
    
    // Connect or reconnect to WiFi
    if(WiFi.status() != WL_CONNECTED){
      Serial.print("Attempting to connect");
      while(WiFi.status() != WL_CONNECTED){
        WiFi.begin(ssid, password); 
        delay(5000);     
      } 
      Serial.println("\nConnected.");
    }

    Serial.print("Glucose Value: ");
    Serial.println(glucose);
    

   // print a random number from 10 to 1023
    randNumber = random(10, 1024);
    
    Serial.println(randNumber);

    
    // Write to ThingSpeak. There are up to 8 fields in a channel, allowing you to store up to 8 different
    // pieces of information in a channel.  Here, we write to field 1.
    int x = ThingSpeak.writeField(myChannelNumber, 1, randNumber, myWriteAPIKey);

    if(x == 200){
      Serial.println("Channel update successful.");
    }
    else{
      Serial.println("Problem updating channel. HTTP error code " + String(x));
    }
    lastTime = millis();
  }
}
