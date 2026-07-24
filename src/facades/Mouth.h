//================================================================
// OttoFlow - facades/Mouth.h
// Expressive layer over modules/Matrix.h. Zero overhead: every
// call inlines straight to the module underneath.
//================================================================
#pragma once
#include "../modules/Matrix.h"

namespace Mouth {
  inline void show(Icon icon)                { Matrix::drawIcon(icon); }
  inline void showDigit(uint8_t digit)       { Matrix::drawDigit(digit); }
  inline void clear()                        { Matrix::clear(); }
  inline void setBrightness(uint8_t level)   { Matrix::setBrightness(level); }
  inline void scrollText(const char* text, uint8_t scrollSpeedMs = 50) {
    Matrix::scrollText(text, scrollSpeedMs);
  }
}
