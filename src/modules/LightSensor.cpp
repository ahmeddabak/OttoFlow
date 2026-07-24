#include "LightSensor.h"
#include "../core/Internal.h"

using ottoflow_internal::config;

namespace LightSensor {

int raw() {
  return analogRead(config().lightSensor.pin);
}

uint8_t brightnessPercent() {
  // Inverted like the official example: typical LDR wiring reads
  // LOWER values in brighter light.
  int inverted = 1023 - raw();
  return (uint8_t)((inverted * 100L) / 1023L);
}

bool isDarkerThanPercent(uint8_t thresholdPercent) {
  return brightnessPercent() < thresholdPercent;
}

bool isBrighterThanPercent(uint8_t thresholdPercent) {
  return brightnessPercent() > thresholdPercent;
}

}  // namespace LightSensor
