 /*
 * Right now this is just a copy / paste of the IridiumSBD
 * SendReceive example.
 * 
 * We should test / modify this code to get basic communications
 * working on our RockBlock and then integrate with sensors & payload mgmt software.
 * 
 * Requires: https://github.com/mikalhart/IridiumSBD
 */

#include <IridiumSBD.h>
#include <SoftwareSerial.h>

//SoftwareSerial nss(17, 16); // RockBLOCK serial port on 16/17 (or 17/16?!)
//IridiumSBD isbd(nss, 10); // RockBLOCK SLEEP pin on 10
IridiumSBD isbd(Serial2);

void setup()
{
  int signalQuality = -1;

  Serial.begin(115200);
  Serial.println("Hello there!");
  //nss.begin(19200);
  Serial2.begin(19200);

  // Allows monitoring / debug when computer is plugged in with USB
  isbd.attachConsole(Serial);
  isbd.attachDiags(Serial);
  Serial.println("Beginning...");
  isbd.begin(); // Wake up the 9602 and prepare it for communications.

  isbd.setPowerProfile(0);

  Serial.println("About to get SignalQuality...");
  int err = isbd.getSignalQuality(signalQuality);
  if (err != 0)
  {
    Serial.print("SignalQuality failed: error ");
    Serial.println(err);
    return;
  }

  Serial.print("Signal quality is ");
  Serial.println(signalQuality);

  /*uint8_t buffer[200] = 
  { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };
  size_t bufferSize = sizeof(buffer);

  // First 2 params are the message to send and its length
  // Second 2 params are the variable to receive the message and the variable length
  err = isbd.sendReceiveSBDBinary(buffer, 20, buffer, bufferSize);
  if (err != 0)
  {
    Serial.print("sendReceiveSBDText failed: error ");
    Serial.println(err);
    return;
  }

  Serial.print("Inbound buffer size is ");
  Serial.println(bufferSize);
  for (int i=0; i<bufferSize; ++i)
  {
    Serial.write(buffer[i]);
    Serial.print("(");
    Serial.print(buffer[i], HEX);
    Serial.print(") ");
  }
  Serial.print("Messages left: ");
  Serial.println(isbd.getWaitingMessageCount());*/

  // Basic send
  err = isbd.sendSBDText("Hello, world!");
  if (err != 0)
  {
    Serial.print("sendSBDText failed: error ");
    Serial.println(err);
    return;
  }

  Serial.println("Hey, it worked!");
  Serial.print("Messages left: ");
  Serial.println(isbd.getWaitingMessageCount());
}

void loop()
{
}
