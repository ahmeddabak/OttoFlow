#include "SoundSensor.h"
#include "../core/Internal.h"

using ottoflow_internal::config;

namespace SoundSensor {

int rawLevel() {
  return analogRead(config().soundSensor.pin);
}

uint8_t loudnessPercent(uint16_t sampleWindowMs) {
  // Sample for the window and track the min/max swing around the
  // sensor's resting midpoint - the swing is the loudness.
  int lowest = 1023, highest = 0;
  unsigned long start = millis();
  do {
    int sample = rawLevel();
    if (sample < lowest)  lowest  = sample;
    if (sample > highest) highest = sample;
  } while (millis() - start < sampleWindowMs);

  int swing = highest - lowest;               // 0..1023
  return (uint8_t)((swing * 100L) / 1023L);   // 0..100 %
}

bool isLouderThanPercent(uint8_t thresholdPercent, uint16_t sampleWindowMs) {
  return loudnessPercent(sampleWindowMs) > thresholdPercent;
}

}  // namespace SoundSensor
