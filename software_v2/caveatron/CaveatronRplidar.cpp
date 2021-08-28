#include "CaveatronRplidar.h"
#include <SoftwareSerial.h>
//#include "RPLidar.h"
#include "rplidar_driver_impl.h"

const int lidarOnPin = 39;
const int lidarMotorPin = 35;

RPLidar rplidar;
char report[25];

void CaveatronRplidar::setup(){
  pinMode(lidarOnPin, OUTPUT);
  digitalWrite(lidarOnPin, HIGH);

  rplidar.begin();
  pinMode(lidarMotorPin, OUTPUT);
  delay(1000);
}

void CaveatronRplidar::printInfo(){
  rplidar_response_device_info_t info;
  rplidar.getDeviceInfo(info);

  char report[100];
  snprintf(report, sizeof(report), "model: %d firmware: %d.%d", info.model, info.firmware_version/256, info.firmware_version%256);
  Serial.println(report);
  delay(1000);
}

void CaveatronRplidar::printSampleDuration(){
  rplidar_response_sample_rate_t sampleInfo;
  rplidar.getSampleDuration_uS(sampleInfo);

  char report[100];
  snprintf(report, sizeof(report), "TStandard: %d[us] TExpress: %d[us]", sampleInfo.std_sample_duration_us, sampleInfo.express_sample_duration_us);
  Serial.println(report);
  delay(1000);
}

void CaveatronRplidar::loop(){
  static int cnt=0;
  // printInfo();
  // printSampleDuration();
  if (!rplidar.isScanning()){
    rplidar.startScanNormal(true);
    analogWrite(lidarMotorPin, 255);
    delay(10);
  }
  cnt++;
  if (RESULT_DATA_READY == rplidar.loopScanData()){
    rplidar_response_measurement_node_hq_t nodes[512];
    rplidar.grabScanData(nodes);

    snprintf(report, sizeof(report), "%d", cnt);
    Serial.println(report);
    cnt = 0;
  }
}

#if 0
void CaveatronRplidar::loop(){
    //rplidar_response_sample_rate_t sampleInfo;
    //if (IS_OK(rplidar.getSampleRate(sampleInfo))){
        //snprintf(report, sizeof(report), "-- %d %d", sampleInfo.t_standard, sampleInfo.t_express);
        //Serial.println(report);
    //}
    //delay(10);

  static int cnt = 0;
  if (IS_OK(rplidar.waitPoint())) {
    float distance = rplidar.getCurrentPoint().distance; //distance value in mm unit
    float angle    = rplidar.getCurrentPoint().angle; //anglue value in degree
    bool  startBit = rplidar.getCurrentPoint().startBit; //whether this point is belong to a new scan
    byte  quality  = rplidar.getCurrentPoint().quality; //quality of the current measurement
    
    //perform data processing here... 
    //snprintf(report, sizeof(report), "%.2f %.2f %d", distance, angle, quality);
    //Serial.println(report);
    if (startBit == true){
        snprintf(report, sizeof(report), "%d", cnt);
        Serial.println(report);
        cnt = 0;
    }
    else {
        cnt++;
    }
  } else {
    analogWrite(lidarMotorPin, 0); //stop the rplidar motor
    
    // try to detect RPLIDAR... 
    rplidar_response_device_info_t info;
    //if (IS_OK(rplidar.getDeviceInfo(info))) {
    if(true){
       // detected...
        rplidar.startExpressScan();
       
       // start motor rotating at max allowed speed
       analogWrite(lidarMotorPin, 255);
       delay(10);
    }
  }
}
#endif
