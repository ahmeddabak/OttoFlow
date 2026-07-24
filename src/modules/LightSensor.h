//================================================================
// OttoFlow - modules/LightSensor.h
// Photoresistor (LDR): how bright is the environment?
// Matches the official Otto_photoresistorTest example: brighter
// light = higher percentage.
//================================================================
#pragma once
#include <Arduino.h>

namespace LightSensor {
  // One raw ADC sample, 0..1023 (wiring-dependent direction).
  int raw();

  // Brightness as 0 (dark) .. 100 (bright) %.
  uint8_t brightnessPercent();

  // Convenience checks.
  bool isDarkerThanPercent(uint8_t thresholdPercent);
  bool isBrighterThanPercent(uint8_t thresholdPercent);
}
