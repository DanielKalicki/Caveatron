#ifndef DISPLAY_H
#define DISPLAY_H


class Display {
  private:
    const int backlightPin = 10;

  public:
    void setup();
    void loop();
    void readDisplayIdInfo();
    void entryModeSet();
    void displayOn();
    void sleepOut();
};

#endif
