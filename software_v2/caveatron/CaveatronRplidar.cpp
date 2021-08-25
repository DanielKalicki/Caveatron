#include "CaveatronRplidar.h"
#include <SoftwareSerial.h>
#include "RPLidar.h"

const int lidarOnPin = 39;
const int lidarMotorPin = 35;

RPLidar rplidar;
char report[80];

void CaveatronRplidar::setup(){
  pinMode(lidarOnPin, OUTPUT);
  digitalWrite(lidarOnPin, HIGH);

  rplidar.begin();
  pinMode(lidarMotorPin, OUTPUT);
  delay(2000);
}

void CaveatronRplidar::loop(){
  if (IS_OK(rplidar.waitPoint())) {
    float distance = rplidar.getCurrentPoint().distance; //distance value in mm unit
    float angle    = rplidar.getCurrentPoint().angle; //anglue value in degree
    bool  startBit = rplidar.getCurrentPoint().startBit; //whether this point is belong to a new scan
    byte  quality  = rplidar.getCurrentPoint().quality; //quality of the current measurement
    
    //perform data processing here... 
    snprintf(report, sizeof(report), "%f %f", distance, angle);
    Serial.println(report);
  } else {
    analogWrite(lidarMotorPin, 0); //stop the rplidar motor
    
    // try to detect RPLIDAR... 
    rplidar_response_device_info_t info;
    if (IS_OK(rplidar.getDeviceInfo(info, 100))) {
       // detected...
       rplidar.startScan();
       
       // start motor rotating at max allowed speed
       analogWrite(lidarMotorPin, 100);
       //delay(1000);
    }
  }
}
