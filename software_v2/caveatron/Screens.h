
#ifndef SCREENS_H
#define SCREENS_H
#include "XPT2046_Touchscreen.h"

void MainMenuDraw();
void MainMenuHandleTouch(TS_Point p);

void SettingsMenuDraw();
void SettingsMenuHandleTouch(TS_Point p);

void ShotModeDraw();
void ShotModeHandleTouch(TS_Point p);

void PassageModeDraw();
void PassageModeHandleTouch(TS_Point p);

void RoomModeDraw();
void RoomModeHandleTouch(TS_Point p);

void ManualModeDraw();
void ManualModeHandleTouch(TS_Point p);

void SurveyMenuDraw();
void SurveyMenuHandleTouch(TS_Point p);

void StationEntryDraw();
void StationEntryHandleTouch(TS_Point p);

void TraverseEntryDraw();
void TraverseEntryHandleTouch(TS_Point p);

void SplayEntryDraw();
void SplayEntryHandleTouch(TS_Point p);

void TimeUnitsDraw();
void TimeUnitsHandleTouch(TS_Point p);

void SDCardDraw();
void SDCardHandleTouch(TS_Point p);

void CalibrateDraw();
void CalibrateHandleTouch(TS_Point p);

void LIDARViewDraw();
void LIDARViewHandleTouch(TS_Point p);

void AboutDraw();
void AboutHandleTouch(TS_Point p);

void ShotStationSelectDraw();
void ShotStationSelectHandleTouch(TS_Point p);

void SetTimeDateDraw();
void SetTimeDateHandleTouch(TS_Point p);

void TimeDateEntryDraw();
void TimeDateEntryHandleTouch(TS_Point p);

void SDCardInfoDraw();
void SDCardInfoHandleTouch(TS_Point p);

void CompassCalibrateDraw();
void CompassCalibrateHandleTouch(TS_Point p);

void FileNameEntryDraw();
void FileNameEntryHandleTouch(TS_Point p);

void CaveNameEntryDraw();
void CaveNameEntryHandleTouch(TS_Point p);

void SurveyStatsDraw();
void SurveyStatsHandleTouch(TS_Point p);

void LinePlotDraw();
void LinePlotHandleTouch(TS_Point p);

void ShotViewerDraw();
void ShotViewerHandleTouch(TS_Point p);

void ScanViewerDraw();
void ScanViewerHandleTouch(TS_Point p);

void ShotScanReviewDraw();
void ShotScanReviewHandleTouch(TS_Point p);

void AdvancedCalDraw();
void AdvancedCalHandleTouch(TS_Point p);

void RawRecordDraw();
void RawRecordHandleTouch(TS_Point p);

void CalShotsDraw();
void CalShotsHandleTouch(TS_Point p);

void CheckCalibrationDraw();
void CheckCalibrationHandleTouch(TS_Point p);

void LoadSaveCalibrationDraw();
void LoadSaveCalibrationHandleTouch(TS_Point p);

#endif
