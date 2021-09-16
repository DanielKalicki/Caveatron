# based on https://github.com/obromios/jrt_laser/blob/master/laser.cpp
#include "JrtLaser.h"
#include <Arduino.h>

const int laserOnPin = 15;
const int laserRxPin = 31;
const int laserTxPin = 32;
#define laserSerial Serial4

void read(char *buffer){
  uint32_t timeout = 500;
  uint32_t currentTs = millis();
  uint32_t remainingtime;
  uint32_t idx = 0;
  while ((remainingtime=millis() - currentTs) <= timeout) {
    int currentbyte = laserSerial.read();
    if (currentbyte < 0){
      continue;
    }
    buffer[idx] = currentbyte;
    idx++;
  }
}

void JrtLaser::setup(){
  pinMode(laserOnPin, OUTPUT);
  digitalWrite(laserOnPin, HIGH);

  pinMode(laserRxPin, INPUT);
  pinMode(laserTxPin, OUTPUT);
  laserSerial.begin(19200);
}

void JrtLaser::loop(){
}

void JrtLaser::on(){
  int nBytesAnswer = 9;
  byte commandStr[] = {0xAA, 0x00, 0x01, 0xBE, 0x00, 0x01, 0x00, 0x01, 0xC1};
  laserSerial.write(commandStr, sizeof(commandStr));
  laserSerial.flush();
  char buffer[nBytesAnswer];
  read(buffer);
}

void JrtLaser::single_shot(){
  int nBytesAnswer = 13;
  byte commandStr[] = {0xAA, 0x00, 0x00, 0x20, 0x00, 0x01, 0x00, 0x00, 0x21};
  laserSerial.write(commandStr, sizeof(commandStr));
  laserSerial.flush();
  delay(150); // wait for measurement
  char buffer[nBytesAnswer];
  read(buffer);
  if (buffer[0] == 0xAA){
    unsigned long distance = (unsigned long) buffer[6] << 24
      | (unsigned long)  buffer[7] << 16
      | (unsigned long)  buffer[8] << 8
      | (unsigned long)  buffer[9];
    unsigned long signalQuality = (unsigned long) buffer[10] << 8
      | (unsigned long)  buffer[11];
    char report[70];
    snprintf(report, sizeof(report), "%ld %ld",
      distance, signalQuality);
    Serial.println(report);
  }
}

