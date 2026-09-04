#include "Matrix.h"
#include "../core/Internal.h"
#include <Otto.h>

using ottoflow_internal::config;
using ottoflow_internal::drv;

namespace Matrix {

// What drawBitmap() last put on the matrix, in picture coordinates.
// Every pixel costs a full 16-bit software-SPI transfer through the
// driver, so redrawing only what changed turns a 64-write frame into a
// handful of writes for blinks and bars. Any other draw call bypasses
// the copy and marks it stale, so the next frame is written in full.
static uint8_t s_shadow[8];
static bool    s_shadowValid = false;

// Map the framework's Icon enum to OttoDIYLib mouth-table ids.
static uint8_t mouthIdFor(Icon icon) {
  switch (icon) {
    case Icon::Heart:         return heart;
    case Icon::Happy:         return happyOpen;
    case Icon::HappyClosed:   return happyClosed;
    case Icon::Smile:         return smile;
    case Icon::Sad:           return sad;
    case Icon::SadOpen:       return sadOpen;
    case Icon::SadClosed:     return sadClosed;
    case Icon::Angry:         return angry;
    case Icon::Surprised:     return bigSurprise;
    case Icon::SmallSurprise: return smallSurprise;
    case Icon::Confused:      return confused;
    case Icon::TongueOut:     return tongueOut;
    case Icon::Vampire1:      return vamp1;
    case Icon::Vampire2:      return vamp2;
    case Icon::Line:          return lineMouth;
    case Icon::Diagonal:      return diagonal;
    case Icon::Ok:            return okMouth;
    case Icon::X:             return xMouth;
    case Icon::Question:      return interrogation;
    case Icon::Thunder:       return thunder;
    case Icon::Culito:        return culito;
  }
  return lineMouth;  // unreachable, keeps the compiler happy
}

// Light one pixel given in picture coordinates (x from the left, y from
// the top), rotated the same way the driver rotates its own mouths and
// scrolling text, so a custom icon comes out the same way up as the
// built-in ones whatever config.matrix.orientation says.
static void plotRotated(uint8_t x, uint8_t y, bool on) {
  uint8_t v = on ? 1 : 0;
  switch (config().matrix.orientation) {
    case 2:  drv().setLed(7 - x, 7 - y, v); break;
    case 3:  drv().setLed(7 - y, x, v);     break;
    case 4:  drv().setLed(y, 7 - x, v);     break;
    default: drv().setLed(x, y, v);         break;
  }
}

void drawIcon(Icon icon) {
  s_shadowValid = false;
  drv().putMouth(mouthIdFor(icon));
}

void drawCustomIcon(const CustomIcon& icon) {
  uint8_t rows[8];
  memcpy_P(rows, icon.rows, sizeof(rows));
  drawBitmap(rows);
}

void drawBitmap(const uint8_t rows[8]) {
  for (uint8_t y = 0; y < 8; y++) {
    uint8_t changed = s_shadowValid ? (rows[y] ^ s_shadow[y]) : 0xFF;
    for (uint8_t x = 0; x < 8; x++) {
      uint8_t bit = 0x80 >> x;
      if (changed & bit) plotRotated(x, y, rows[y] & bit);
    }
    s_shadow[y] = rows[y];
  }
  s_shadowValid = true;
}

void drawDigit(uint8_t digit) {
  if (digit > 9) return;
  s_shadowValid = false;
  drv().putMouth(digit);  // mouth ids 0..9 are the digits
}

void drawMouthId(uint8_t mouthId) {
  if (mouthId >= NUMBER_OF_ELEMENTS) return;
  s_shadowValid = false;
  drv().putMouth(mouthId);
}

void drawPixel(uint8_t x, uint8_t y, bool on) {
  s_shadowValid = false;
  drv().setLed(x, y, on ? 1 : 0);
}

void drawPattern(unsigned long pattern) {
  s_shadowValid = false;
  drv().putMouth(pattern, false);
}

void scrollText(const char* text, uint8_t scrollSpeedMs) {
  s_shadowValid = false;
  drv().writeText(text, scrollSpeedMs);
}

void setBrightness(uint8_t level) {
  drv().matrixIntensity(level > 15 ? 15 : level);
}

void clear() {
  drv().clearMouth();
  memset(s_shadow, 0, sizeof(s_shadow));   // a blank frame is a known frame
  s_shadowValid = true;
}

}  // namespace Matrix
