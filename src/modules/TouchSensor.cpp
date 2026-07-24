#include "TouchSensor.h"
#include "../core/Internal.h"

using ottoflow_internal::config;

namespace TouchSensor {

bool isTouched() {
  return digitalRead(config().touch.pin) == HIGH;
}

bool wasTapped() {
  static bool          lastState    = false;
  static bool          primed       = false;
  static unsigned long lastChangeMs = 0;

  bool state = digitalRead(config().touch.pin) == HIGH;

  if (!primed) {               // first call: learn the resting state
    lastState = state;
    primed = true;
    return false;
  }

  if (state != lastState && (millis() - lastChangeMs) > 50) {  // 50 ms debounce
    bool rose = state;   // true when the pin just went HIGH
    lastState = state;
    lastChangeMs = millis();
    // Momentary mode: a touch is the rising edge only (ignore release).
    // Toggle mode: every state change is one touch.
    return config().touch.toggleMode ? true : rose;
  }
  return false;
}

}  // namespace TouchSensor
