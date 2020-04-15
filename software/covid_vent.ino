/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Blink
*/
const int directionPin1 = 12;
const int directionPin2 = 2;
const int enablePin = 4;

//const int tidalVolume = 400; // 200 ml
const int tidalVolume = 500; //
//const int tidalVolume = 600; //

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(directionPin1, OUTPUT);
  pinMode(directionPin2, OUTPUT);
  pinMode(enablePin, OUTPUT);
}

// the loop fun)tion runs over and over again forever
void loop() {
  for(int i=0; i<tidalVolume; i++)
  {
    // Set to inspiration
    digitalWrite(directionPin1, LOW);
    digitalWrite(directionPin2, HIGH);
    digitalWrite(LED_BUILTIN, HIGH);   // pulse the motor HIGH
    delayMicroseconds(2000);  // wait 1 milli-second
    digitalWrite(LED_BUILTIN, LOW);    // pulse the moto LOW
    delayMicroseconds(2000);  
  }
  delay(100);                       // wait for a second
  for(int i=0; i<tidalVolume; i++)
  {
    // Set to expiration
    digitalWrite(directionPin1, HIGH);
    digitalWrite(directionPin2, LOW);
    digitalWrite(LED_BUILTIN, HIGH);   // pulse the motor HIGH
    delayMicroseconds(2000);  // wait 1 milli-second
    digitalWrite(LED_BUILTIN, LOW);    // pulse the moto LOW
    delayMicroseconds(2000);
  }
  delay(2000);
}
