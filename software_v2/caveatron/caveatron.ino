#include <Wire.h>
#include <SoftwareSerial.h>
#include "LSM303.h"
#include "SdCard.h"

const int ledPin = 13;
const int buzzerPin = 36;
const int lidarOnPin = 39;

SdCardClass card;

LSM303 sensors;

const int lidarRxPin = 34;
const int lidarTxPin = 33;
SoftwareSerial lidarSerial(lidarRxPin, lidarTxPin);

char report[80];

void setup(){
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(lidarOnPin, OUTPUT);
  digitalWrite(lidarOnPin, HIGH);

  pinMode(lidarRxPin, INPUT);
  pinMode(lidarTxPin, OUTPUT);
  lidarSerial.begin(115200);

  card.setup();
  /*Wire.setClock(400000);*/
  /*Wire.setSCL(37);*/
  /*Wire.setSDA(38);*/
  Wire.begin();
  sensors.init();
  sensors.enableDefault();
  digitalWrite(buzzerPin, HIGH);
  delay(500);
  digitalWrite(buzzerPin, LOW);
}

void loop(){
  digitalWrite(ledPin, HIGH);
  delay(1);
  digitalWrite(ledPin, LOW);
  /*sensors.readAcc();*/
  /*snprintf(report, sizeof(report), "A: %6d %6d %6d    M: %6d %6d %6d",*/
    /*sensors.a.x, sensors.a.y, sensors.a.z,*/
    /*sensors.m.x, sensors.m.y, sensors.m.z);*/
  lidarSerial.print("\xA5\x52");
  while(lidarSerial.available() > 0) {
    int lidarData = lidarSerial.read();
    Serial.print(lidarData, HEX);
    Serial.print(" ");
  }
  Serial.println("");
  delay(200);
}
