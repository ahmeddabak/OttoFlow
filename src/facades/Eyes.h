//================================================================
// OttoFlow - facades/Eyes.h
// Expressive layer over modules/Ultrasonic.h. Zero overhead:
// every call inlines straight to the module underneath.
//================================================================
#pragma once
#include "../modules/Ultrasonic.h"

namespace Eyes {
  /** Distance value returned when nothing is within range. */
  constexpr long OUT_OF_RANGE_CM = Ultrasonic::OUT_OF_RANGE_CM;

  /** @return distance to the nearest object in cm, or OUT_OF_RANGE_CM if none. */
  inline long distanceCm()               { return Ultrasonic::distanceCm(); }
  /** @return true if the nearest object is closer than @p cm. */
  inline bool closerThanCm(long cm)      { return Ultrasonic::distanceCm() < cm; }
  /** @return true if the nearest object is farther than @p cm. */
  inline bool fartherThanCm(long cm)     { return Ultrasonic::distanceCm() > cm; }
}
