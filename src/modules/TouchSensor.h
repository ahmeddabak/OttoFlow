//================================================================
// OttoFlow - modules/TouchSensor.h
// The TTP223 touch sensor (or any push button) on an input pin.
//
// Works with both sensor modes:
//  - momentary: output HIGH only while touched
//  - toggle:    output flips state on every touch (some kits ship
//               like this) - use wasTapped(), which detects any
//               state change, so it works in either mode.
//================================================================
#pragma once
#include <Arduino.h>

namespace TouchSensor {
  // Current raw state of the sensor pin (HIGH = touched, in
  // momentary mode; meaningless as "touched" in toggle mode).
  bool isTouched();

  // True exactly once per touch: detects a state CHANGE since the
  // last call. Works in momentary and toggle mode. Call it every
  // loop() iteration.
  bool wasTapped();
}
