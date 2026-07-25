//================================================================
// OttoFlow - facades/Touch.h
// Expressive layer over modules/TouchSensor.h. Zero overhead.
//================================================================
#pragma once
#include "../modules/TouchSensor.h"

namespace Touch {
  /** @return true while the sensor is being touched (level, momentary). */
  inline bool isTouched() { return TouchSensor::isTouched(); }
  /** @return true once per tap (edge); clears after it is read. */
  inline bool wasTapped() { return TouchSensor::wasTapped(); }
}
