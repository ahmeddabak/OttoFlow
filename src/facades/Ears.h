//================================================================
// OttoFlow - facades/Ears.h
// Expressive layer over modules/SoundSensor.h (the microphone).
// Zero overhead.
//================================================================
#pragma once
#include "../modules/SoundSensor.h"

namespace Ears {
  /** @return current ambient loudness as a percentage (0..100). */
  inline uint8_t loudnessPercent() { return SoundSensor::loudnessPercent(); }

  /**
   * @return true when loudness exceeds @p thresholdPercent.
   * Handy for clap detection, e.g. Ears::hearsSoundLouderThanPercent(60).
   */
  inline bool hearsSoundLouderThanPercent(uint8_t thresholdPercent) {
    return SoundSensor::isLouderThanPercent(thresholdPercent);
  }
}
