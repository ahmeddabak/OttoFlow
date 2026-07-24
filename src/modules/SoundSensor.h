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
  // One raw ADC sample of the sensor output, 0..1023.
  int rawLevel();

  // Peak loudness over a short sampling window, as 0..100 %.
  // (Sound is a wave - a single sample can hit a zero crossing,
  // so we take the peak of many samples.)
  uint8_t loudnessPercent(uint16_t sampleWindowMs = 50);

  // True when the loudness in the window exceeds the threshold -
  // e.g. a clap: isLouderThanPercent(60).
  bool isLouderThanPercent(uint8_t thresholdPercent,
                           uint16_t sampleWindowMs = 50);
}
