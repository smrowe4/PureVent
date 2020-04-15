const int TxPin = 1;

#include <SoftwareSerial.h>
SoftwareSerial mySerial = SoftwareSerial(255, TxPin);

int peep = 5;
int tidal_volume = 500;
int bpm = 15;
int pressure = 22;

void setup() {
    
  pinMode(TxPin, OUTPUT);
  digitalWrite(TxPin, HIGH);
  
  mySerial.begin(9600);
  delay(100);
  mySerial.write(12);
  mySerial.write(17);
  delay(50);
}

void loop() {
  update_serial_display();
  delay(1000);
  
}
void update_serial_display()
{
  mySerial.write(128); //move to: first line, first char
  String str1 = "BPM: " + String(bpm, DEC) + " tv: " + String(tidal_volume, DEC);
  mySerial.print(str1);  // First line
  mySerial.write(148);
  String str2 =  "P: " + String(pressure, DEC) + " PEEP: " + String(peep, DEC);
  mySerial.print(str2);
  //mySerial.write(18);                 // Turn backlight off
}
