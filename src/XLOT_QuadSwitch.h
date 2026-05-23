#pragma once
#include <Arduino.h>
#include <Wire.h>

class XLOT_QuadSwitch {
public:
  explicit XLOT_QuadSwitch(TwoWire& wire = Wire);

  bool begin(uint8_t address = 0x32);

  uint8_t readAllSwitches();         // bit0~bit3
  uint8_t readSwitch(uint8_t index); // 返回 0 或 1

  bool setLED(uint8_t index, uint8_t r, uint8_t g, uint8_t b, uint8_t brightness);
  bool setLEDColor(uint8_t index, uint8_t r, uint8_t g, uint8_t b);
  bool setLEDBrightness(uint8_t index, uint8_t brightness);

private:
  TwoWire* _wire;
  uint8_t _addr;

  uint8_t readReg(uint8_t reg);
  bool writeReg(uint8_t reg, uint8_t value);
  bool writeRegs(uint8_t reg, const uint8_t* data, size_t len);
};