# XLOT-QuadSwitch

Arduino library for the XLOT-QuadSwitch RGB button module.

This library can:

- Read 4 switch states over I2C
- Control 4 RGB LEDs independently
- Set LED color and brightness
- Run on XLOT / ESP32 Arduino boards

## Default I2C Address

```cpp
0x32
```

## Basic Wiring

For XLOT-Hermes / ESP32 example:

```cpp
Wire.begin(17, 18); // SDA, SCL
```

## Install from ZIP

1. Download this repository as a ZIP file.
2. Open Arduino IDE.
3. Go to **Sketch > Include Library > Add .ZIP Library...**
4. Select the ZIP file.
5. Open examples from **File > Examples > XLOT-QuadSwitch**.

## Example Programs

- `XLOT_QuadSwitch_test`: read all switches and set 4 LED colors.
- `XLOT_QuadSwitch_switch_to_led`: switch state controls corresponding LED color.
- `XLOT_QuadSwitch_RGB_Effect`: smooth RGB flowing effect.

## Minimal Example

```cpp
#include <Wire.h>
#include "XLOT_QuadSwitch.h"

XLOT_QuadSwitch quad(Wire);

void setup() {
  Serial.begin(115200);
  Wire.begin(17, 18);
  quad.begin(0x32);

  quad.setLED(0, 255, 0, 0, 40);
}

void loop() {
  Serial.println(quad.readSwitch(0));
  delay(100);
}
```

## Website

http://www.xlot.tech
