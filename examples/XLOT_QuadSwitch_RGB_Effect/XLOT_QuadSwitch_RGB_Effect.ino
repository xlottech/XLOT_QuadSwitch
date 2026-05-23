#include <Wire.h>
#include "XLOT_QuadSwitch.h"

XLOT_QuadSwitch quad(Wire);

struct RGB {
  uint8_t r;
  uint8_t g;
  uint8_t b;
};

// 按你上面的例子整理成 6 个首尾相连的颜色点
// 颜色环：粉橙 -> 黄 -> 绿 -> 青 -> 蓝 -> 紫 -> 回到粉橙
const RGB palette[6] = {
  {255, 125, 125},  // 粉橙
  {255, 255, 125},  // 黄
  {125, 255, 125},  // 绿
  {125, 255, 255},  // 青
  {125, 125, 255},  // 蓝
  {255, 125, 255}   // 紫粉
};

float phase = 0.0f;                 // 整体相位
const float speed = 0.03f;          // 速度，越大越快
const float ledOffset = 1.0f;       // 每个灯错开 1 段，和你原来的感觉接近
const uint8_t ledBrightness = 60;   // 每路亮度 0~255
const uint16_t frameMs = 20;        // 刷新间隔

unsigned long lastFrame = 0;
unsigned long lastPrint = 0;

RGB lerpColor(const RGB& a, const RGB& b, float t) {
  RGB out;
  out.r = (uint8_t)(a.r + (b.r - a.r) * t);
  out.g = (uint8_t)(a.g + (b.g - a.g) * t);
  out.b = (uint8_t)(a.b + (b.b - a.b) * t);
  return out;
}

RGB getPaletteColor(float p) {
  while (p < 0.0f) p += 6.0f;
  while (p >= 6.0f) p -= 6.0f;

  int seg = (int)p;           // 0~5
  float t = p - seg;          // 当前段内插值 0~1

  RGB c1 = palette[seg];
  RGB c2 = palette[(seg + 1) % 6];

  return lerpColor(c1, c2, t);
}

void updateQuadSwitchRGB() {
  for (uint8_t i = 0; i < 4; i++) {
    // 4个灯在同一个颜色环上错开
    float p = phase - i * ledOffset;
    RGB c = getPaletteColor(p);
    quad.setLED(i, c.r, c.g, c.b, ledBrightness);
  }
}

void printSwitchStates() {
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
}

void setup() {
  Serial.begin(115200);
  Wire.begin(17,18);        // ESP32可改成 Wire.begin(SDA, SCL);
  quad.begin(0x32);

  updateQuadSwitchRGB();
}

void loop() {
  unsigned long now = millis();

  // RGB 动画
  if (now - lastFrame >= frameMs) {
    lastFrame = now;

    updateQuadSwitchRGB();

    phase += speed;
    if (phase >= 6.0f) {
      phase -= 6.0f;
    }
  }

  // 顺便打印一下4路按键 0/1
  if (now - lastPrint >= 200) {
    lastPrint = now;
    printSwitchStates();
  }
}