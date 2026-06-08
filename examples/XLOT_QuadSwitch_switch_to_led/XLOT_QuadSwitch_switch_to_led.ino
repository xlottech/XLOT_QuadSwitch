/*
quad.setLED(0, 255,   0,   0,  40);
鍙傛暟璇存槑NOTE:锛堢鍑犱釜鐏彔which RGB(0-3)锛孯(0-255),G(0-255),B(0-255)锛屼寒搴rightness(0-255)锛?*/
#include <Wire.h>
#include "XLOT_QuadSwitch.h"

XLOT_QuadSwitch quad(Wire);

void setup() {
  Serial.begin(115200);
  Wire.begin(17,18);
  quad.begin(0x32);
}

void loop() {
  for (uint8_t i = 0; i < 4; i++) {
    uint8_t v = quad.readSwitch(i);

    if (v == 1) {
      quad.setLED(i, 0, 255, 0, 40);   // 寮€ = 缁?    } else {
      quad.setLED(i, 255, 0, 0, 40);   // 鍏?= 绾?    }
  }

  Serial.print("SW1=");
  Serial.print(quad.readSwitch(0));
  Serial.print(" SW2=");
  Serial.print(quad.readSwitch(1));
  Serial.print(" SW3=");
  Serial.print(quad.readSwitch(2));
  Serial.print(" SW4=");
  Serial.println(quad.readSwitch(3));

  delay(100);
}