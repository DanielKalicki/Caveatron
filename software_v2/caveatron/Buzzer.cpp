#include "Buzzer.h"
#include <Arduino.h>

void Buzzer::setup(){
  pinMode(buzzerPin, OUTPUT);

  // test
  digitalWrite(buzzerPin, HIGH);
  delay(500);
  digitalWrite(buzzerPin, LOW);
}

void Buzzer::on(){
}

void Buzzer::off(){
}
