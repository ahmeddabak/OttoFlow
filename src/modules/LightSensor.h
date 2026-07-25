//================================================================
// OttoFlow - modules/LightSensor.h
// Photoresistor (LDR): how bright is the environment?
// Matches the official Otto_photoresistorTest example: brighter
// light = higher percentage.
//================================================================
#pragma once
#include <Arduino.h>

namespace LightSensor {
  /** @return one raw ADC sample, 0..1023 (direction depends on wiring). */
  int raw();

  /** @return brightness as 0 (dark) .. 100 (bright) %. */
  uint8_t brightnessPercent();

  /** @return true when brightness is below @p thresholdPercent. */
  bool isDarkerThanPercent(uint8_t thresholdPercent);
  /** @return true when brightness is above @p thresholdPercent. */
  bool isBrighterThanPercent(uint8_t thresholdPercent);
}
