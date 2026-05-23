#include "XLOT_QuadSwitch.h"

XLOT_QuadSwitch::XLOT_QuadSwitch(TwoWire& wire) {
  _wire = &wire;
  _addr = 0x32;
}

bool XLOT_QuadSwitch::begin(uint8_t address) {
  _addr = address;
  return true;
}

uint8_t XLOT_QuadSwitch::readReg(uint8_t reg) {
  _wire->beginTransmission(_addr);
  _wire->write(reg);
  if (_wire->endTransmission(false) != 0) {
    return 0;
  }

  if (_wire->requestFrom((int)_addr, 1) != 1) {
    return 0;
  }

  return _wire->read();
}

bool XLOT_QuadSwitch::writeReg(uint8_t reg, uint8_t value) {
  _wire->beginTransmission(_addr);
  _wire->write(reg);
  _wire->write(value);
  return (_wire->endTransmission() == 0);
}

bool XLOT_QuadSwitch::writeRegs(uint8_t reg, const uint8_t* data, size_t len) {
  _wire->beginTransmission(_addr);
  _wire->write(reg);
  for (size_t i = 0; i < len; i++) {
    _wire->write(data[i]);
  }
  return (_wire->endTransmission() == 0);
}

uint8_t XLOT_QuadSwitch::readAllSwitches() {
  return readReg(0x00);
}

uint8_t XLOT_QuadSwitch::readSwitch(uint8_t index) {
  if (index >= 4) return 0;
  return readReg(0x01 + index);
}

bool XLOT_QuadSwitch::setLED(uint8_t index, uint8_t r, uint8_t g, uint8_t b, uint8_t brightness) {
  if (index >= 4) return false;

  uint8_t reg = 0x10 + index * 4;
  uint8_t buf[4] = {r, g, b, brightness};
  return writeRegs(reg, buf, 4);
}

bool XLOT_QuadSwitch::setLEDColor(uint8_t index, uint8_t r, uint8_t g, uint8_t b) {
  if (index >= 4) return false;

  uint8_t reg = 0x10 + index * 4;
  uint8_t buf[3] = {r, g, b};
  return writeRegs(reg, buf, 3);
}

bool XLOT_QuadSwitch::setLEDBrightness(uint8_t index, uint8_t brightness) {
  if (index >= 4) return false;

  uint8_t reg = 0x10 + index * 4 + 3;
  return writeReg(reg, brightness);
}