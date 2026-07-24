#include "Ultrasonic.h"
#include "../core/Internal.h"

using ottoflow_internal::config;

namespace Ultrasonic {

unsigned long echoMicros() {
  const UltrasonicConfig& cfg = config().ultrasonic;
  digitalWrite(cfg.triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(cfg.triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(cfg.triggerPin, LOW);
  return pulseIn(cfg.echoPin, HIGH, cfg.timeoutMicros);
}

long readSingleCm() {
  unsigned long duration = echoMicros();
  if (duration == 0) return OUT_OF_RANGE_CM;  // timeout: no echo
  return (long)(duration / 58);
}

long distanceCm() {
  const UltrasonicConfig& cfg = config().ultrasonic;

  uint8_t n = cfg.samples;
  if (!cfg.medianFilter || n <= 1) return readSingleCm();
  if (n > 5) n = 5;

  long readings[5];
  for (uint8_t i = 0; i < n; i++) {
    readings[i] = readSingleCm();
    if (i + 1 < n) delay(5);   // let the previous ping fade
  }

  // Insertion sort (n <= 5), then take the middle value.
  for (uint8_t i = 1; i < n; i++) {
    long value = readings[i];
    int8_t j = i - 1;
    while (j >= 0 && readings[j] > value) {
      readings[j + 1] = readings[j];
      j--;
    }
    readings[j + 1] = value;
  }
  return readings[n / 2];
}

}  // namespace Ultrasonic
