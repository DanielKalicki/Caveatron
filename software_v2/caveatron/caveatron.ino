#include <Wire.h>
#include <math.h>
#include <SoftwareSerial.h>
#include "LIS3MDL.h"
#include "LSM6.h"
#include "SdCard.h"
#include "Buzzer.h"
#include "CaveatronRplidar.h"
#include "Display.h"
#include "JrtLaser.h"
#include "XPT2046_Touchscreen.h"
#include <SPI.h>
#include "SoftSPI.h"
#include "Screens.h"
#include <string>

const int ledPin = 13;

LIS3MDL mag;
LSM6 imu;
TeensySdCard card;
Buzzer buzzer;
CaveatronRplidar lidar;
Display disp;
JrtLaser laser;
const uint8_t tsCsPin = 25;
const uint8_t tsMosiPin = 26;
const uint8_t tsMisoPin = 27;
const uint8_t tsSckPin = 24;
XPT2046_Touchscreen ts(tsCsPin);
SoftSPI tsSPI(tsMosiPin, tsMisoPin, tsSckPin);
#define Wire Wire1

enum screenModes{
  screenMainMenu,
  screenSettingsMenu,
  screenShotMode,
  screenPassageMode,
  screenRoomMode,
  screenManualMode,
  screenSurveyMenu,
  screenStationEntry,
  screenTraverseEntry,
  screenSplayEntry,
  screenTimeUnits,
  screenSDCard,
  screenCalibrate,
  screenLIDARView,
  screenAbout,
  screenShotStationSelect,
  screenSetTimeDate,
  screenTimeDateEntry,
  screenSDCardInfo,
  screenCompassCalibrate,
  screenFileNameEntry,
  screenCaveNameEntry,
  screenSurveyStats,
  screenLinePlot,
  screenShotViewer,
  screenScanViewer,
  screenShotScanReview,
  screenAdvancedCal,
  screenRawRecord,
  screenCalShots,
  screenCheckCalibration,
  screenLoadSaveCalibration
};

enum menuModes{
  modeNull,
  modeShot,
  modePassage,
  modeRoom,
  modeManual,
  modeSurvey,
  modeSetTime,
  modeLIDARView,
  modeRawLive,
  modeCalRec1000,
  modeCalRecCont,
  modeCalShots,
  modeEditSurvey,
  modeViewScans
};

struct caveatronStatus{
  screenModes screen;
  std::string caveName;
  struct{
    std::string name;
  } currentStation;
} caveatron;

void setup(){
  // pinMode(ledPin, OUTPUT);

  Serial.begin(115200);

  card.setup();

  Wire.begin();
  if (!mag.init()) Serial.println("magnetometer initialization failed");
  mag.enableDefault();

  if (!imu.init()) Serial.println("IMU initialization failed");
  imu.enableDefault();

  // lidar.setup();
  buzzer.setup();

  disp.setup();

  ts.begin(tsSPI);
  ts.setRotation(1);

  // initialize caveatron structure
  // arduino ide does not support anonymous members
  caveatron.screen=screenMainMenu;
  caveatron.caveName="";
  caveatron.currentStation.name="";
}
void loop(){
  static uint8_t screenTick = 0;
  static uint8_t touchDebounce = 0;

  if (screenTick >= 100){
    switch (caveatron.screen){
      case screenMainMenu: MainMenuDraw(); break;
      case screenSettingsMenu: SettingsMenuDraw(); break;
      case screenShotMode: ShotModeDraw(); break;
      case screenPassageMode: PassageModeDraw(); break;
      case screenRoomMode: RoomModeDraw(); break;
      case screenManualMode: ManualModeDraw(); break;
      case screenSurveyMenu: SurveyMenuDraw(); break;
      case screenStationEntry: StationEntryDraw(); break;
      case screenTraverseEntry: TraverseEntryDraw(); break;
      case screenSplayEntry: SplayEntryDraw(); break;
      case screenTimeUnits: TimeUnitsDraw(); break;
      case screenSDCard: SDCardDraw(); break;
      case screenCalibrate: CalibrateDraw(); break;
      case screenLIDARView: LIDARViewDraw(); break;
      case screenAbout: AboutDraw(); break;
      case screenShotStationSelect: ShotStationSelectDraw(); break;
      case screenSetTimeDate: SetTimeDateDraw(); break;
      case screenTimeDateEntry: TimeDateEntryDraw(); break;
      case screenSDCardInfo: SDCardInfoDraw(); break;
      case screenCompassCalibrate: CompassCalibrateDraw(); break;
      case screenFileNameEntry: FileNameEntryDraw(); break;
      case screenCaveNameEntry: CaveNameEntryDraw(); break;
      case screenSurveyStats: SurveyStatsDraw(); break;
      case screenLinePlot: LinePlotDraw(); break;
      case screenShotViewer: ShotViewerDraw(); break;
      case screenScanViewer: ScanViewerDraw(); break;
      case screenShotScanReview: ShotScanReviewDraw(); break;
      case screenAdvancedCal: AdvancedCalDraw(); break;
      case screenRawRecord: RawRecordDraw(); break;
      case screenCalShots: CalShotsDraw(); break;
      case screenCheckCalibration: CheckCalibrationDraw(); break;
      case screenLoadSaveCalibration: LoadSaveCalibrationDraw(); break;
      default: break;
    }
    screenTick = 0;
  }
  screenTick +=1;

  if (touchDebounce < 10){ touchDebounce++; }
  if (ts.touched() && touchDebounce >= 10){
    TS_Point p = ts.getPoint();
    switch (caveatron.screen){
      case screenMainMenu: MainMenuHandleTouch(p); break;
      case screenSettingsMenu: SettingsMenuHandleTouch(p); break;
      case screenShotMode: ShotModeHandleTouch(p); break;
      case screenPassageMode: PassageModeHandleTouch(p); break;
      case screenRoomMode: RoomModeHandleTouch(p); break;
      case screenManualMode: ManualModeHandleTouch(p); break;
      case screenSurveyMenu: SurveyMenuHandleTouch(p); break;
      case screenStationEntry: StationEntryHandleTouch(p); break;
      case screenTraverseEntry: TraverseEntryHandleTouch(p); break;
      case screenSplayEntry: SplayEntryHandleTouch(p); break;
      case screenTimeUnits: TimeUnitsHandleTouch(p); break;
      case screenSDCard: SDCardHandleTouch(p); break;
      case screenCalibrate: CalibrateHandleTouch(p); break;
      case screenLIDARView: LIDARViewHandleTouch(p); break;
      case screenAbout: AboutHandleTouch(p); break;
      case screenShotStationSelect: ShotStationSelectHandleTouch(p); break;
      case screenSetTimeDate: SetTimeDateHandleTouch(p); break;
      case screenTimeDateEntry: TimeDateEntryHandleTouch(p); break;
      case screenSDCardInfo: SDCardInfoHandleTouch(p); break;
      case screenCompassCalibrate: CompassCalibrateHandleTouch(p); break;
      case screenFileNameEntry: FileNameEntryHandleTouch(p); break;
      case screenCaveNameEntry: CaveNameEntryHandleTouch(p); break;
      case screenSurveyStats: SurveyStatsHandleTouch(p); break;
      case screenLinePlot: LinePlotHandleTouch(p); break;
      case screenShotViewer: ShotViewerHandleTouch(p); break;
      case screenScanViewer: ScanViewerHandleTouch(p); break;
      case screenShotScanReview: ShotScanReviewHandleTouch(p); break;
      case screenAdvancedCal: AdvancedCalHandleTouch(p); break;
      case screenRawRecord: RawRecordHandleTouch(p); break;
      case screenCalShots: CalShotsHandleTouch(p); break;
      case screenCheckCalibration: CheckCalibrationHandleTouch(p); break;
      case screenLoadSaveCalibration: LoadSaveCalibrationHandleTouch(p); break;
      default: break;
    }
    Serial.print("Pressure = ");
    Serial.print(p.z);
    Serial.print(", x = ");
    Serial.print(p.x);
    Serial.print(", y = ");
    Serial.print(p.y);
    Serial.println();
    touchDebounce = 0;
  }

  //calibrationLoop();

  // digitalWrite(ledPin, HIGH);
  // delay(100);
  // digitalWrite(ledPin, LOW);

  // Serial.println("0");

  // mag.read();
  // char report[80];
  // // LIS3MDL::vector<float>mag_;
  // // mag_.x = (float)mag.m.x;
  // // mag_.y = (float)mag.m.y;
  // // mag_.z = (float)mag.m.z;
  // // LIS3MDL::vector_normalize(&mag_);
  // // snprintf(report, sizeof(report), "M: %.4f %.4f %.4f",
  // //   mag_.x, mag_.y, mag_.z);
  // float heading = atan2(mag.m.y, mag.m.x) * (180 / PI);
  // snprintf(report, sizeof(report), "M: %6d %6d %6d %f",
  //   mag.m.x, mag.m.y, mag.m.z, heading);
  // Serial.println(report);

  // // imu.read();
  // // snprintf(report, sizeof(report), "A: %6d %6d %6d    G: %6d %6d %6d",
  // //   imu.a.x, imu.a.y, imu.a.z,
  // //   imu.g.x, imu.g.y, imu.g.z);
  // // Serial.println(report);

  delay(10);

  // laser.single_shot();

  // disp.loop();
}
