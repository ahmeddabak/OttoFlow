//================================================================
// OttoFlow - facades/Balance.h
// Expressive layer over modules/Mpu6050.h (the motion sensor -
// Otto's inner ear). Zero overhead. Requires
// config.mpu6050.enabled = true.
//================================================================
#pragma once
#include "../modules/Mpu6050.h"

namespace Balance {
  inline float pitchDegrees() { return Mpu6050::pitchDegrees(); }
  inline float rollDegrees()  { return Mpu6050::rollDegrees(); }

  inline bool isLevelWithinDegrees(float toleranceDegrees = 15) {
    return Mpu6050::isLevelWithinDegrees(toleranceDegrees);
  }
  inline bool isUpsideDown() { return Mpu6050::isUpsideDown(); }
  inline bool isShakenHarderThanG(float thresholdG = 0.6) {
    return Mpu6050::isShakenHarderThanG(thresholdG);
  }
}
