#include <Wire.h>
#include "XLOT_QuadSwitch.h"

XLOT_QuadSwitch quad(Wire);

void setup() {
  Serial.begin(115200);
  Wire.begin(17,18);   //  Wire.begin(SDA, SCL);
  quad.begin(0x32);

  // 姣忎竴璺崟鐙缃鑹插拰浜害
  /*
  quad.setLED(0, 255,   0,   0,  40);
  鍙傛暟璇存槑NOTE:锛堢鍑犱釜鐏彔which RGB(0-3)锛孯(0-255),G(0-255),B(0-255)锛屼寒搴rightness(0-255)锛?  */  
  quad.setLED(0, 255,   0,   0,  40);   // 1璺?绾㈣壊 浜害40(0-255)
  quad.setLED(1,   0, 255,   0,  40);   // 2璺?缁胯壊 浜害40(0-255)
  quad.setLED(2,   0,   0, 255,  40);   // 3璺?钃濊壊 浜害40(0-255)
  quad.setLED(3, 255, 255,   0,  40);   // 4璺?榛勮壊 浜害40(0-255)
}

void loop() {
  uint8_t sw1 = quad.readSwitch(0);
  uint8_t sw2 = quad.readSwitch(1);
  uint8_t sw3 = quad.readSwitch(2);
  uint8_t sw4 = quad.readSwitch(3);

  Serial.print("SW1=");
  Serial.print(sw1);
  Serial.print("  SW2=");
  Serial.print(sw2);
  Serial.print("  SW3=");
  Serial.print(sw3);
  Serial.print("  SW4=");
  Serial.println(sw4);

  delay(100);
}