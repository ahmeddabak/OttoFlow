//================================================================
// OttoFlow - modules/Matrix.h
// The 8x8 MAX7219 LED matrix. Full control: named icons, digits,
// raw mouth-table ids, single pixels, scrolling text, brightness.
//================================================================
#pragma once
#include <Arduino.h>
#include "../core/Icons.h"

namespace Matrix {
  void drawIcon(Icon icon);
  void drawDigit(uint8_t digit);            // 0..9
  void drawMouthId(uint8_t mouthId);        // raw OttoDIYLib mouth index 0..30
  void drawPixel(uint8_t x, uint8_t y, bool on);
  void scrollText(const char* text, uint8_t scrollSpeedMs = 50);
  void setBrightness(uint8_t level);        // 0 (dim) .. 15 (bright)
  void clear();
}
