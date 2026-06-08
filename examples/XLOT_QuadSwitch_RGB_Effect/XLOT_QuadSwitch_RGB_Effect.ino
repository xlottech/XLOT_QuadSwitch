/*
quad.setLED(0, 255,   0,   0,  40);
鍙傛暟璇存槑NOTE:锛堢鍑犱釜鐏彔which RGB(0-3)锛孯(0-255),G(0-255),B(0-255)锛屼寒搴rightness(0-255)锛?*/
#include <Wire.h>
#include "XLOT_QuadSwitch.h"

XLOT_QuadSwitch quad(Wire);

struct RGB {
  uint8_t r;
  uint8_t g;
  uint8_t b;
};

// 鎸変綘涓婇潰鐨勪緥瀛愭暣鐞嗘垚 6 涓灏剧浉杩炵殑棰滆壊鐐?// 棰滆壊鐜細绮夋 -> 榛?-> 缁?-> 闈?-> 钃?-> 绱?-> 鍥炲埌绮夋
const RGB palette[6] = {
  {255, 125, 125},  // 绮夋
  {255, 255, 125},  // 榛?  {125, 255, 125},  // 缁?  {125, 255, 255},  // 闈?  {125, 125, 255},  // 钃?  {255, 125, 255}   // 绱矇
};

float phase = 0.0f;                 // 鏁翠綋鐩镐綅
const float speed = 0.03f;          // 閫熷害锛岃秺澶ц秺蹇?const float ledOffset = 1.0f;       // 姣忎釜鐏敊寮€ 1 娈碉紝鍜屼綘鍘熸潵鐨勬劅瑙夋帴杩?const uint8_t ledBrightness = 60;   // 姣忚矾浜害 0~255
const uint16_t frameMs = 20;        // 鍒锋柊闂撮殧

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
  float t = p - seg;          // 褰撳墠娈靛唴鎻掑€?0~1

  RGB c1 = palette[seg];
  RGB c2 = palette[(seg + 1) % 6];

  return lerpColor(c1, c2, t);
}

void updateQuadSwitchRGB() {
  for (uint8_t i = 0; i < 4; i++) {
    // 4涓伅鍦ㄥ悓涓€涓鑹茬幆涓婇敊寮€
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
  Wire.begin(17,18);        // ESP32鍙敼鎴?Wire.begin(SDA, SCL);
  quad.begin(0x32);

  updateQuadSwitchRGB();
}

void loop() {
  unsigned long now = millis();

  // RGB 鍔ㄧ敾
  if (now - lastFrame >= frameMs) {
    lastFrame = now;

    updateQuadSwitchRGB();

    phase += speed;
    if (phase >= 6.0f) {
      phase -= 6.0f;
    }
  }

  // 椤轰究鎵撳嵃涓€涓?璺寜閿?0/1
  if (now - lastPrint >= 200) {
    lastPrint = now;
    printSwitchStates();
  }
}