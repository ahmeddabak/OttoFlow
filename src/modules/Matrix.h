//================================================================
// OttoFlow - modules/Matrix.h
// The 8x8 MAX7219 LED matrix. Full control: named icons, digits,
// raw mouth-table ids, single pixels, scrolling text, brightness.
//================================================================
#pragma once
#include <Arduino.h>
#include "../core/Icons.h"

namespace Matrix {
  /** Draw a named expression (see the Icon enum). */
  void drawIcon(Icon icon);
  /** Draw a single digit, 0..9. */
  void drawDigit(uint8_t digit);
  /** Draw a raw OttoDIYLib mouth by index, 0..30. */
  void drawMouthId(uint8_t mouthId);
  /** Turn a single pixel on or off at (@p x, @p y). */
  void drawPixel(uint8_t x, uint8_t y, bool on);
  /** Draw a raw 30-bit mouth pattern (6x5 grid). */
  void drawPattern(unsigned long pattern);
  /** Scroll @p text across the matrix; @p scrollSpeedMs is the per-step delay. */
  void scrollText(const char* text, uint8_t scrollSpeedMs = 50);
  /** Set the brightness level, 0 (dim) .. 15 (bright). */
  void setBrightness(uint8_t level);
  /** Turn every LED off. */
  void clear();
}
