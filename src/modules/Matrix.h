//================================================================
// OttoFlow - modules/Matrix.h
// The 8x8 MAX7219 LED matrix. Full control: named icons, your own
// 8x8 icons, digits, raw mouth-table ids, single pixels, scrolling
// text, brightness.
//================================================================
#pragma once
#include <Arduino.h>
#include "../core/Icons.h"

namespace Matrix {
  /** Draw a named expression (see the Icon enum). */
  void drawIcon(Icon icon);
  /**
   * Draw an 8x8 icon of your own (see OTTOFLOW_ICON in core/Icons.h).
   * Honours the configured matrix orientation like the built-in icons.
   */
  void drawCustomIcon(const CustomIcon& icon);
  /**
   * Draw a full 8x8 frame from RAM: @p rows holds eight bytes, top row
   * first, most significant bit = leftmost pixel. Use it for pictures
   * you build at runtime (bars, meters); prefer drawCustomIcon() for
   * fixed art, which then lives in flash.
   */
  void drawBitmap(const uint8_t rows[8]);
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
