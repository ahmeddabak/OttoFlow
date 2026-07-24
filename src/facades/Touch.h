//================================================================
// OttoFlow - facades/Touch.h
// Expressive layer over modules/TouchSensor.h. Zero overhead.
//================================================================
#pragma once
#include "../modules/TouchSensor.h"

namespace Touch {
  inline bool isTouched() { return TouchSensor::isTouched(); }
  inline bool wasTapped() { return TouchSensor::wasTapped(); }
}
