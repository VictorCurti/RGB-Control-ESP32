#include <Arduino.h>
#include <IRremote.h> // include the IRremote library

#define RECEIVER_PIN 13         // define the IR receiver pin
#define LED 2
IRrecv receiver(RECEIVER_PIN); // create a receiver object of the IRrecv class

#define Bt_ON   4228116224
#define Bt_OFF  4244827904

void setup()
{
  Serial.begin(9600);     // begin serial communication with a baud rate of 9600
  receiver.enableIRIn();  // enable the receiver
  Serial.println("SISTEMA ON");

  pinMode(LED, OUTPUT);
  digitalWrite(LED,LOW);

}

void loop()
{
  if (receiver.decode())
  {
    Serial.println("RECEBIDO");
    Serial.println(receiver.decodedIRData.decodedRawData);
    
    if(receiver.decodedIRData.decodedRawData == Bt_ON)
    {
      digitalWrite(LED, HIGH);
      delay(100);
    }

    if (receiver.decodedIRData.decodedRawData == Bt_OFF)
    {
      digitalWrite(LED, LOW);
      delay(100);
    }

    receiver.resume();
  }
}