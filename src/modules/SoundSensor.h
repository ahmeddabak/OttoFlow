//================================================================
// OttoFlow - modules/SoundSensor.h
// Analog microphone / sound sensor. Reads the loudness of the
// environment - claps, voices, music.
//
// Safe to call before the sensor is wired: an unconnected analog
// pin just returns noise.
//================================================================
#pragma once
#include <Arduino.h>

namespace SoundSensor {
  /** @return one raw ADC sample of the sensor output, 0..1023. */
  int rawLevel();

  /**
   * @return peak loudness over a @p sampleWindowMs window, as 0..100 %.
   * Sound is a wave - a single sample can land on a zero crossing, so
   * this takes the peak of many samples across the window.
   */
  uint8_t loudnessPercent(uint16_t sampleWindowMs = 50);

  /**
   * @return true when loudness in the @p sampleWindowMs window exceeds
   * @p thresholdPercent - e.g. a clap: isLouderThanPercent(60).
   */
  bool isLouderThanPercent(uint8_t thresholdPercent,
                           uint16_t sampleWindowMs = 50);
}
