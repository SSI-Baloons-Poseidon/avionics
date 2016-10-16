/*
 * Right now this is just a copy / paste of the IridiumSBD
 * SendReceive example.
 * 
 * We should test / modify this code to get basic communications
 * working on our RockBlock and then integrate with sensors & payload mgmt software.
 */

#include <IridiumSBD.h>
#include <SoftwareSerial.h>

SoftwareSerial nss(18, 19); // RockBLOCK serial port on 18/19
IridiumSBD isbd(nss, 10); // RockBLOCK SLEEP pin on 10

void setup()
{
  int signalQuality = -1;

  Serial.begin(115200);
  nss.begin(19200);

  // Allows monitoring / debug when computer is plugged in with USB
  isbd.attachConsole(Serial);
  isbd.attachDiags(Serial);

  isbd.begin(); // Wake up the 9602 and prepare it for communications.

  isbd.setPowerProfile(1);

  int err = isbd.getSignalQuality(signalQuality);
  if (err != 0)
  {
    Serial.print("SignalQuality failed: error ");
    Serial.println(err);
    return;
  }

  Serial.print("Signal quality is ");
  Serial.println(signalQuality);

  uint8_t buffer[200] = 
  { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };
  size_t bufferSize = sizeof(buffer);
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
  Serial.println(isbd.getWaitingMessageCount());
}

void loop()
{
}
