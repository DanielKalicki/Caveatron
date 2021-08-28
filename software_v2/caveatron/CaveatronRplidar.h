#ifndef RPLIDAR_H
#define RPLIDAR_H

#include <SoftwareSerial.h>
#include <Arduino.h>

class CaveatronRplidar {
  private:
  public:
    void setup();
    void loop();
    void printInfo();
    void printSampleDuration();
};

#endif
