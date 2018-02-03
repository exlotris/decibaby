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
unsigned char toSend = 3;

void setup() {

 // initialize i2c as slave
 Wire.begin(SLAVE_ADDRESS);
 analogReference(EXTERNAL);
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
byte myArray[2];
myArray[0] = (number >> 8) & 0xFF;
myArray[1] = number & 0xFF;
Wire.write(myArray, 2);
}
