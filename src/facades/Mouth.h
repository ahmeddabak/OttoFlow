//================================================================
// OttoFlow - facades/Mouth.h
// Expressive layer over modules/Matrix.h. Zero overhead: every
// call inlines straight to the module underneath.
//================================================================
#pragma once
#include "../modules/Matrix.h"

namespace Mouth {
  /** Show an expression on the LED matrix (see the Icon enum). */
  inline void show(Icon icon)                { Matrix::drawIcon(icon); }
  /** Show a single digit (0..9) on the LED matrix. */
  inline void showDigit(uint8_t digit)       { Matrix::drawDigit(digit); }
  /** Turn every LED off. */
  inline void clear()                        { Matrix::clear(); }
  /** Set the matrix brightness (0 = dim .. 15 = brightest). */
  inline void setBrightness(uint8_t level)   { Matrix::setBrightness(level); }
  /** Scroll @p text across the matrix; @p scrollSpeedMs is the per-step delay. */
  inline void scrollText(const char* text, uint8_t scrollSpeedMs = 50) {
    Matrix::scrollText(text, scrollSpeedMs);
  }
}
