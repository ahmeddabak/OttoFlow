#include "Matrix.h"
#include "../core/Internal.h"
#include <Otto.h>

using ottoflow_internal::drv;

namespace Matrix {

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

void drawIcon(Icon icon) { drv().putMouth(mouthIdFor(icon)); }

void drawDigit(uint8_t digit) {
  if (digit <= 9) drv().putMouth(digit);  // mouth ids 0..9 are the digits
}

void drawMouthId(uint8_t mouthId) {
  if (mouthId < NUMBER_OF_ELEMENTS) drv().putMouth(mouthId);
}

void drawPixel(uint8_t x, uint8_t y, bool on) { drv().setLed(x, y, on ? 1 : 0); }

void scrollText(const char* text, uint8_t scrollSpeedMs) {
  drv().writeText(text, scrollSpeedMs);
}

void setBrightness(uint8_t level) {
  drv().matrixIntensity(level > 15 ? 15 : level);
}

void clear() { drv().clearMouth(); }

}  // namespace Matrix
