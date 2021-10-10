
screens = [
  "screenMainMenu",
  "screenSettingsMenu",
  "screenShotMode",
  "screenPassageMode",
  "screenRoomMode",
  "screenManualMode",
  "screenSurveyMenu",
  "screenStationEntry",
  "screenTraverseEntry",
  "screenSplayEntry",
  "screenTimeUnits",
  "screenSDCard",
  "screenCalibrate",
  "screenLIDARView",
  "screenAbout",
  "screenShotStationSelect",
  "screenSetTimeDate",
  "screenTimeDateEntry",
  "screenSDCardInfo",
  "screenCompassCalibrate",
  "screenFileNameEntry",
  "screenCaveNameEntry",
  "screenSurveyStats",
  "screenLinePlot",
  "screenShotViewer",
  "screenScanViewer",
  "screenShotScanReview",
  "screenAdvancedCal",
  "screenRawRecord",
  "screenCalShots",
  "screenCheckCalibration",
  "screenLoadSaveCalibration"
];

# .h file
for screen in screens:
	name = screen.replace("screen", "")
	print("")
	print("void " + name + "Draw();")
	print("void " + name + "HandleTouch(TS_Point p);")

print("----------------")

#.cpp file
for screen in screens:
	name = screen.replace("screen", "")
	print("")
	print("void " + name + "Draw(){")
	print("")
	print("}")
	print("void " + name + "HandleTouch(TS_Point p){")
	print("")
	print("}")

print("----------------")

#screen switch
for screen in screens:
	name = screen.replace("screen", "")
	print("      case " + screen + ": " + name + "Draw(); break;")

print("----------------")

#screen touch switch
for screen in screens:
	name = screen.replace("screen", "")
	print("      case " + screen + ": " + name + "HandleTouch(p); break;")