#include <Wire.h>
 
#define SLAVE_ADDRESS 0x04
int number = 0;
int state = 0;
int analogPin = 3;
int volt = 0;
 
void setup() {
 pinMode(13, OUTPUT);
 
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
 Wire.write(number);
}
