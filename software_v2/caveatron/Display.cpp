
#include "Display.h"
#include <Arduino.h>

#define TFT_CS   3  // Chip select control pin, active low
#define CS_L digitalWrite(TFT_CS, LOW)
#define CS_H digitalWrite(TFT_CS, HIGH)

#define TFT_DC  23 // Data Command control pin - must use a pin in the range 0-31, DC=1 DB bits are RAM data or command parameters, DC=0 DB bits are commands
#define DC_L digitalWrite(TFT_DC, LOW)
#define DC_H digitalWrite(TFT_DC, HIGH)

#define TFT_RST  4  // Reset pin - active low
#define RST_L digitalWrite(TFT_RST, LOW)
#define RST_H digitalWrite(TFT_RST, HIGH)

#define TFT_WR    22  // Write strobe control pin - must use a pin in the range 0-31, data latched on rising edge
#define WR_L digitalWrite(TFT_WR, LOW)
#define WR_H digitalWrite(TFT_WR, HIGH)

#define TFT_RD    // Parallel data read strobe
#define RD_L //digitalWrite(TFT_RD, LOW)
#define RD_H //digitalWrite(TFT_RD, HIGH)

#define TFT_D0   16 // Must use pins in the range 0-31 for the data bus
#define TFT_D1   17 // so a single register write sets/clears all bits
#define TFT_D2   19
#define TFT_D3   18
#define TFT_D4   0
#define TFT_D5   1 
#define TFT_D6   29
#define TFT_D7   30
#define TFT_D8   2
#define TFT_D9   14
#define TFT_D10   7
#define TFT_D11   14
#define TFT_D12   6
#define TFT_D13   20
#define TFT_D14   21
#define TFT_D15   5

void tft_Write_8(uint16_t data){
  digitalWrite(TFT_D0, ((data & 0x01) > 0) ? HIGH : LOW);
  digitalWrite(TFT_D1, ((data & 0x02) > 0) ? HIGH : LOW);
  digitalWrite(TFT_D2, ((data & 0x04) > 0) ? HIGH : LOW);
  digitalWrite(TFT_D3, ((data & 0x08) > 0) ? HIGH : LOW);
  digitalWrite(TFT_D4, ((data & 0x10) > 0) ? HIGH : LOW);
  digitalWrite(TFT_D5, ((data & 0x20) > 0) ? HIGH : LOW);
  digitalWrite(TFT_D6, ((data & 0x40) > 0) ? HIGH : LOW);
  digitalWrite(TFT_D7, ((data & 0x80) > 0) ? HIGH : LOW);
}

uint16_t tft_Read_8(){
  uint16_t data = 0x00;
  data += digitalRead(TFT_D0);
  data += digitalRead(TFT_D1) << 1;
  data += digitalRead(TFT_D2) << 2;
  data += digitalRead(TFT_D3) << 3;
  data += digitalRead(TFT_D4) << 4;
  data += digitalRead(TFT_D5) << 5;
  data += digitalRead(TFT_D6) << 6;
  data += digitalRead(TFT_D7) << 7;
  return data;
}

void tft_Write_16(uint16_t data){
  digitalWrite(TFT_D0, ((data & 0x01) > 0) ? HIGH : LOW);
  digitalWrite(TFT_D1, ((data & 0x02) > 0) ? HIGH : LOW);
  digitalWrite(TFT_D2, ((data & 0x04) > 0) ? HIGH : LOW);
  digitalWrite(TFT_D3, ((data & 0x08) > 0) ? HIGH : LOW);
  digitalWrite(TFT_D4, ((data & 0x10) > 0) ? HIGH : LOW);
  digitalWrite(TFT_D5, ((data & 0x20) > 0) ? HIGH : LOW);
  digitalWrite(TFT_D6, ((data & 0x40) > 0) ? HIGH : LOW);
  digitalWrite(TFT_D7, ((data & 0x80) > 0) ? HIGH : LOW);
  digitalWrite(TFT_D8, ((data & 0x0100) > 0) ? HIGH : LOW);
  digitalWrite(TFT_D9, ((data & 0x0200) > 0) ? HIGH : LOW);
  digitalWrite(TFT_D10, ((data & 0x0400) > 0) ? HIGH : LOW);
  digitalWrite(TFT_D11, ((data & 0x0800) > 0) ? HIGH : LOW);
  digitalWrite(TFT_D12, ((data & 0x1000) > 0) ? HIGH : LOW);
  digitalWrite(TFT_D13, ((data & 0x2000) > 0) ? HIGH : LOW);
  digitalWrite(TFT_D14, ((data & 0x4000) > 0) ? HIGH : LOW);
  digitalWrite(TFT_D15, ((data & 0x8000) > 0) ? HIGH : LOW);
}

void setDataMode(uint8_t mode){
  pinMode(TFT_D0, mode);
  pinMode(TFT_D1, mode);
  pinMode(TFT_D2, mode);
  pinMode(TFT_D3, mode);
  pinMode(TFT_D4, mode);
  pinMode(TFT_D5, mode);
  pinMode(TFT_D6, mode);
  pinMode(TFT_D7, mode);
  pinMode(TFT_D8, mode);
  pinMode(TFT_D9, mode);
  pinMode(TFT_D10, mode);
  pinMode(TFT_D11, mode);
  pinMode(TFT_D12, mode);
  pinMode(TFT_D13, mode);
  pinMode(TFT_D14, mode);
  pinMode(TFT_D15, mode);
}

void sendData(uint8_t);
void sendCommand(uint8_t);

void writeData(uint8_t data){sendData(data);}
void writeCommand(uint8_t data){sendCommand(data);}

void Display::setup(){

  pinMode(TFT_CS, OUTPUT);
  CS_H;
  pinMode(TFT_DC, OUTPUT);
  DC_H;

  pinMode(TFT_RST, OUTPUT);
  RST_L;
  delay(100);
  RST_H;
  delay(100);

  pinMode(TFT_WR, OUTPUT);
  WR_H;
  // pinMode(TFT_RD, OUTPUT);
  // RD_H;

  setDataMode(OUTPUT);
  while(1){
    // tft_Write_16(0x0400+0x0800+0x1000);
    // tft_Write_16(0x1000);
    WR_H;
    DC_H;
    delay(1000);
    WR_L;
    DC_L;
    delay(1000);
  }

  return;

  delay(500);

  entryModeSet();
  delay(200);
  sleepOut();
  delay(200);
  displayOn();
  delay(500);

  pinMode(backlightPin, OUTPUT);
  digitalWrite(backlightPin, LOW);

  writeCommand(0x53); // Change display brightness
  writeData(0x2C);

  writeCommand(0x51); // Change display brightness
  writeData(0xAF);

//   CS_L;
//     writeCommand(0xE0); // Positive Gamma Control
//     writeData(0x00);
//     writeData(0x03);
//     writeData(0x09);
//     writeData(0x08);
//     writeData(0x16);
//     writeData(0x0A);
//     writeData(0x3F);
//     writeData(0x78);
//     writeData(0x4C);
//     writeData(0x09);
//     writeData(0x0A);
//     writeData(0x08);
//     writeData(0x16);
//     writeData(0x1A);
//     writeData(0x0F);

//     writeCommand(0XE1); // Negative Gamma Control
//     writeData(0x00);
//     writeData(0x16);
//     writeData(0x19);
//     writeData(0x03);
//     writeData(0x0F);
//     writeData(0x05);
//     writeData(0x32);
//     writeData(0x45);
//     writeData(0x46);
//     writeData(0x04);
//     writeData(0x0E);
//     writeData(0x0D);
//     writeData(0x35);
//     writeData(0x37);
//     writeData(0x0F);

//     writeCommand(0XC0); // Power Control 1
//     writeData(0x17);
//     writeData(0x15);

//     writeCommand(0xC1); // Power Control 2
//     writeData(0x41);

//     writeCommand(0xC5); // VCOM Control
//     writeData(0x00);
//     writeData(0x12);
//     writeData(0x80);

//     writeCommand(0x36); // Memory Access Control
//     writeData(0x48);          // MX, BGR

//     writeCommand(0x3A); // Pixel Interface Format
//     writeData(0x55);  // 16 bit colour for parallel

//     writeCommand(0xB0); // Interface Mode Control
//     writeData(0x00);

//     writeCommand(0xB1); // Frame Rate Control
//     writeData(0xA0);

//     writeCommand(0xB4); // Display Inversion Control
//     writeData(0x02);

//     writeCommand(0xB6); // Display Function Control
//     writeData(0x02);
//     writeData(0x02);
//     writeData(0x3B);

//     writeCommand(0xB7); // Entry Mode Set
//     writeData(0xC6);

//     writeCommand(0xF7); // Adjust Control 3
//     writeData(0xA9);
//     writeData(0x51);
//     writeData(0x2C);
//     writeData(0x82);

//     writeCommand(0x11);  //Exit Sleep
// delay(120);

//     writeCommand(0x29);  //Display on
// delay(25);

//     writeCommand(0x51); // Change display brightness
//     writeData(0xFF);

//   CS_H;
}

void Display::loop(){
  // digitalWrite(backlightPin, HIGH);
  // delay(500);
  // digitalWrite(backlightPin, LOW);
  // delay(500);
}

void sendCommand(uint8_t cmd){
  setDataMode(OUTPUT);
  delay(1);
  RD_H;
  delay(1);
  DC_L;
  delay(1);
  WR_L;
  tft_Write_8(cmd);
  delay(1);
  WR_H; //rising edge
  delay(1);
  DC_H;
  delay(1);
}

void sendData(uint8_t data){
  setDataMode(OUTPUT);
  delay(1);
  RD_H;
  DC_H;
  delay(1);
  WR_L;
  tft_Write_8(data);
  delay(1);
  WR_H; //rising edge
  delay(1);
}

uint16_t readData(){
  setDataMode(INPUT);
  RD_L;
  delay(1);
  RD_H; // rising edge
  uint16_t data = tft_Read_8();
  delay(1);
  return data;
}

void Display::readDisplayIdInfo(){
  CS_L;
  sendCommand(0x09);
  uint16_t data1 = readData();
  uint16_t data2 = readData();
  uint16_t data3 = readData();
  uint16_t data4 = readData();
  CS_H;

  char report[30];
  snprintf(report, sizeof(report), "%d %d %d %d", data1, data2, data3, data4);
  Serial.println(report);

  delay(1000);
}

void Display::displayOn(){
  CS_L;
  sendCommand(0x29);
  CS_H;
}

void Display::sleepOut(){
  CS_L;
  sendCommand(0x11);
  CS_H;
}

void Display::entryModeSet(){
  CS_L;
  sendCommand(0xB7);
  sendData(0xC6);
  CS_H;
}
