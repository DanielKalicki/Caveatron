#ifndef BUZZER_H
#define BUZZER_H

class Buzzer {
  private:
    const int buzzerPin = 36;

  public:
    void setup();
    void on();
    void off();
};

#endif
