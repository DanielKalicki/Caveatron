#include "CaveatronRplidar.h"
#include <SoftwareSerial.h>
#include "RPLidar.h"

const int lidarOnPin = 39;
const int lidarRxPin = 34;
const int lidarTxPin = 33;
const int lidarMotorPin = 35;
SoftwareSerial lidarSerial(lidarRxPin, lidarTxPin);

RPLidar rplidar;
char report[80];

void CaveatronRplidar::setup(){
  pinMode(lidarOnPin, OUTPUT);
  digitalWrite(lidarOnPin, HIGH);

  pinMode(lidarRxPin, INPUT);
  pinMode(lidarTxPin, OUTPUT);
  lidarSerial.begin(115200);

  //rplidar.begin(lidarSerial);
  pinMode(lidarMotorPin, OUTPUT);
  delay(2000);
}

void CaveatronRplidar::loop(){
  //lidarSerial.print("\xA5\x52");
  char cmd[2] = {0xA5, 0x52};
  lidarSerial.write(cmd, 2);
  while(lidarSerial.available() > 0) {
    int lidarData = lidarSerial.read();
    Serial.print(lidarData, HEX);
    Serial.print(" ");
  }
  Serial.println("");
#if 0
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
    Serial.print(1);
    
    // try to detect RPLIDAR... 
    rplidar_response_device_info_t info;
    if (IS_OK(rplidar.getDeviceInfo(info, 100))) {
        Serial.print(2);
       // detected...
       rplidar.startScan();
        Serial.print(3);
       
       // start motor rotating at max allowed speed
       analogWrite(lidarMotorPin, 20);
        Serial.print(4);
       delay(1000);
        Serial.print(5);
    }
    Serial.print("1.5");
  }
#endif
}
