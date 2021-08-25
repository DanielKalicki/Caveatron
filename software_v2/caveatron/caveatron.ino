#include <Wire.h>
#include <SoftwareSerial.h>
#include "LSM303.h"
#include "SdCard.h"
#include "Buzzer.h"
#include "CaveatronRplidar.h"

const int ledPin = 13;

LSM303 sensors;
TeensySdCard card;
Buzzer buzzer;
CaveatronRplidar lidar;

/*char report[80];*/

void setup(){
  pinMode(ledPin, OUTPUT);

  card.setup();
  /*Wire.setClock(400000);*/
  /*Wire.setSCL(37);*/
  /*Wire.setSDA(38);*/
  Wire.begin();
  sensors.init();
  sensors.enableDefault();

  lidar.setup();
  buzzer.setup();
}

void loop(){
  digitalWrite(ledPin, HIGH);
  delay(1);
  digitalWrite(ledPin, LOW);
  /*sensors.readAcc();*/
  /*snprintf(report, sizeof(report), "A: %6d %6d %6d    M: %6d %6d %6d",*/
    /*sensors.a.x, sensors.a.y, sensors.a.z,*/
    /*sensors.m.x, sensors.m.y, sensors.m.z);*/
  lidar.loop();
  delay(20);
}
