#include <Wire.h>

#define SLAVE_ADDRESS 0x04
int number = 0;
int state = 0;
int analogPin = 3;
int volt = 0;
int byteSending = 1;
int toTransfer = 32767;
int Shift = toTransfer;
int mask = 0xFF;

void setup() {

 // initialize i2c as slave
 Wire.begin(SLAVE_ADDRESS);
 
 // define callbacks for i2c communication
 Wire.onReceive(receiveData);
 Wire.onRequest(sendData);
}

void loop() {
  delay(100);
 volt = analogRead(analogPin);
}

// callback for received data
void receiveData(int byteCount)
{
  while(Wire.available())
  {
    number = Wire.read();
    if (number == 1){
      number = volt;
    }
  }
}
// callback for sending data
void sendData(){
 //Wire.write(number);
 if (byteSending == 1) //send packet 1
 {
   number = Shift & mask;
   Shift = Shift >> 8;
   Wire.write(number);
   byteSending = 2;
 }
 else if (byteSending == 2) //send packet 2
 {
   number = Shift & mask;
   Shift = Shift >> 8;
   Wire.write(number);
   byteSending = 3;
 }
 else if (byteSending == 3) //send packet 3
 {
   number = Shift & mask;
   Shift = Shift >> 8;
   Wire.write(number);
   byteSending = 4;
 }
 else if (byteSending == 4) //send packet 4
 {
   number = Shift & mask;
   Shift = Shift >> 8;
   Wire.write(number);
   byteSending = 1;
   //initialization for next turn
   Shift = toTransfer;
   mask = 0xFF;
   number = 0;
 }
}
