//================================================================
// OttoFlow - modules/Ultrasonic.h
// The HC-SR04 distance sensor. distanceCm() applies the configured
// median filter (default: median of 3) to kill false spikes;
// readSingleCm() and echoMicros() give raw access.
//
// Note: readings block for up to `timeoutMicros` (default 25 ms)
// per sample when nothing is in range.
//================================================================
#pragma once
#include <Arduino.h>

namespace Ultrasonic {
  /** Distance value returned when no echo comes back (nothing in range). */
  constexpr long OUT_OF_RANGE_CM = 999;

  /**
   * @return filtered distance in centimeters (median of the configured
   * number of samples), or OUT_OF_RANGE_CM when nothing is in range.
   */
  long distanceCm();

  /** @return one unfiltered distance reading in centimeters. */
  long readSingleCm();

  /** @return raw echo pulse width in microseconds; 0 = no echo (timeout). */
  unsigned long echoMicros();
}
