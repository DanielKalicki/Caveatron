#include "Screens.h"
#include <Arduino.h>

// class to define on screen buttons with function to check if the button isTouched
class Button {
	private:
		int16_t x1, x2, y1, y2;
	public:
		Button(int16_t x1, int16_t y1, int16_t x2, int16_t y2) : x1(x1), x2(x2), y1(y1), y2(y2) {}
		bool isTouched(TS_Point p){
			if (p.x >= x1 && p.x <= x2 && p.y >= y1 && p.y <= y2){
				return true;
			}
			return false;
		}
};

void MainMenuDraw(){

}
void MainMenuHandleTouch(TS_Point p){

}

void SettingsMenuDraw(){

}
void SettingsMenuHandleTouch(TS_Point p){

}

void ShotModeDraw(){

}
void ShotModeHandleTouch(TS_Point p){
	Button takeShot();
	Button cancel();
	// Button UseRight(); // not supported
}

void PassageModeDraw(){

}
void PassageModeHandleTouch(TS_Point p){

}

void RoomModeDraw(){

}
void RoomModeHandleTouch(TS_Point p){

}

void ManualModeDraw(){

}
void ManualModeHandleTouch(TS_Point p){

}

void SurveyMenuDraw(){

}
void SurveyMenuHandleTouch(TS_Point p){

}

void StationEntryDraw(){

}
void StationEntryHandleTouch(TS_Point p){

}

void TraverseEntryDraw(){

}
void TraverseEntryHandleTouch(TS_Point p){

}

void SplayEntryDraw(){

}
void SplayEntryHandleTouch(TS_Point p){

}

void TimeUnitsDraw(){

}
void TimeUnitsHandleTouch(TS_Point p){

}

void SDCardDraw(){

}
void SDCardHandleTouch(TS_Point p){

}

void CalibrateDraw(){

}
void CalibrateHandleTouch(TS_Point p){

}

void LIDARViewDraw(){

}
void LIDARViewHandleTouch(TS_Point p){

}

void AboutDraw(){

}
void AboutHandleTouch(TS_Point p){

}

void ShotStationSelectDraw(){

}
void ShotStationSelectHandleTouch(TS_Point p){
	Button frontX1X2();
	Button frontX1Xunk();
	Button frontXunkXunk();
	Button backX1X2();
	Button backX1Xunk();
	Button backXunkXunk();
}

void SetTimeDateDraw(){

}
void SetTimeDateHandleTouch(TS_Point p){

}

void TimeDateEntryDraw(){

}
void TimeDateEntryHandleTouch(TS_Point p){

}

void SDCardInfoDraw(){

}
void SDCardInfoHandleTouch(TS_Point p){

}

void CompassCalibrateDraw(){

}
void CompassCalibrateHandleTouch(TS_Point p){

}

void FileNameEntryDraw(){

}
void FileNameEntryHandleTouch(TS_Point p){

}

void CaveNameEntryDraw(){

}
void CaveNameEntryHandleTouch(TS_Point p){

}

void SurveyStatsDraw(){

}
void SurveyStatsHandleTouch(TS_Point p){

}

void LinePlotDraw(){

}
void LinePlotHandleTouch(TS_Point p){

}

void ShotViewerDraw(){

}
void ShotViewerHandleTouch(TS_Point p){

}

void ScanViewerDraw(){

}
void ScanViewerHandleTouch(TS_Point p){

}

void ShotScanReviewDraw(){

}
void ShotScanReviewHandleTouch(TS_Point p){

}

void AdvancedCalDraw(){

}
void AdvancedCalHandleTouch(TS_Point p){

}

void RawRecordDraw(){

}
void RawRecordHandleTouch(TS_Point p){

}

void CalShotsDraw(){

}
void CalShotsHandleTouch(TS_Point p){

}

void CheckCalibrationDraw(){

}
void CheckCalibrationHandleTouch(TS_Point p){

}

void LoadSaveCalibrationDraw(){

}
void LoadSaveCalibrationHandleTouch(TS_Point p){

}