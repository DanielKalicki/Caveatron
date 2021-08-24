#ifndef SDCARD_H
#define SDCARD_H

#include <SD.h>
#include <SPI.h>

class SdCardClass {
  private:
    // set up variables using the SD utility library functions:
    Sd2Card card;
    SdVolume volume;
    SdFile root;

    // change this to match your SD shield or module;
    // Arduino Ethernet shield: pin 4
    // Adafruit SD shields and modules: pin 10
    // Sparkfun SD shield: pin 8
    // Teensy audio board: pin 10
    // Teensy 3.5 & 3.6 & 4.1 on-board: BUILTIN_SDCARD
    // Wiz820+SD board: pin 4
    // Teensy 2.0: pin 0
    // Teensy++ 2.0: pin 20
    const int chipSelect = BUILTIN_SDCARD;

  public:
    void setup();
};

#endif
