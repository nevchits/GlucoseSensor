/* The original example can be found at https://github.com/esp8266/Basic/tree/master/libraries/espsoftwareserial
 * Implementation of the Arduino software serial library for the ESP8266.
 * Speed up to 115200 baud is supported. The constructor also has an optional input buffer size.
 * Please note that due to the fact that the ESP always have other activities ongoing, there will be some inexactness in interrupt timings. 
 * This may lead to bit errors when having heavy data traffic in high baud rates.
 * 
 * https://forum.arduino.cc/index.php?topic=354933.0
 * For ESP8266, GPIO 0 ~ 5, 12 ~ 15 can be used for RX / TX, GPIO 16 cannot be used for RX / TX.
 * 
 * The circuit:
 *    RX is digital pin 14 (connect to TX of other device)
 *    TX is digital pin 12 (connect to RX of other device)
 */


#include <SoftwareSerial.h>

SoftwareSerial swSer(14, 12, false);

void setup() {
  Serial.begin(9600);
  swSer.begin(9600);

  Serial.println("Loopback serial test started");

  for (char ch = ' '; ch <= 'z'; ch++) {
    swSer.write(ch);
  }
  swSer.println("");

}

void loop() {
  while (swSer.available() > 0) {
    Serial.write(swSer.read());
  }
  while (Serial.available() > 0) {
    swSer.write(Serial.read());
  }

}
