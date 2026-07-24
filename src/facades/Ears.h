//================================================================
// OttoFlow - facades/Ears.h
// Expressive layer over modules/SoundSensor.h (the microphone).
// Zero overhead.
//================================================================
#pragma once
#include "../modules/SoundSensor.h"

namespace Ears {
  inline uint8_t loudnessPercent() { return SoundSensor::loudnessPercent(); }

  // e.g. a clap: Ears::hearsSoundLouderThanPercent(60)
  inline bool hearsSoundLouderThanPercent(uint8_t thresholdPercent) {
    return SoundSensor::isLouderThanPercent(thresholdPercent);
  }
}
