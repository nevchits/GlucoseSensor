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

String str = "";


SoftwareSerial swSer(14, 12, false);   // rxPin, txPin, inverse_logic, 
//SoftwareSerial swSer(14, 12, false, 256);   // rxPin, txPin, inverse_logic, buffer size

void setup() {
  Serial.begin(9600);
  swSer.begin(9600);                     // Max speed for software serial is 115200bps

  // clear out the serial buffer
  // https://forum.arduino.cc/index.php?topic=234151.0
  // -----------------------------------------------------------------------------------------------------
  byte w = 0;

  for (int i = 0; i < 10; i++) {
      while (Serial.available() > 0) {
          char k = Serial.read();
          w++;
          delay(1);
      }
      delay(1);
  }
  // -----------------------------------------------------------------------------------------------------

  Serial.println();
  //Serial.print("***SSSoooffftttwwwaaarrreee...ssseeerrriiiaaalll...ttteeesssttt...ssstttaaarrrttteeeddd***");
  Serial.print("***Software.serial.test.started***");

  while (swSer.available() > 0) {
      str = str + (char)swSer.read();
      yield();
  }

  Serial.println();
  Serial.print("Message received via software serial: ");
  Serial.println(str);

  Serial.println("\nEnd of message received");
  
}

void loop() {
  yield();
}
