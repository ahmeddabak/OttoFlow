//================================================================
// OttoFlow - facades/Eyes.h
// Expressive layer over modules/Ultrasonic.h. Zero overhead:
// every call inlines straight to the module underneath.
//================================================================
#pragma once
#include "../modules/Ultrasonic.h"

namespace Eyes {
  constexpr long OUT_OF_RANGE_CM = Ultrasonic::OUT_OF_RANGE_CM;

  inline long distanceCm()               { return Ultrasonic::distanceCm(); }
  inline bool closerThanCm(long cm)      { return Ultrasonic::distanceCm() < cm; }
  inline bool fartherThanCm(long cm)     { return Ultrasonic::distanceCm() > cm; }
}
