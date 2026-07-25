//================================================================
// OttoFlow - facades/Balance.h
// Expressive layer over modules/Mpu6050.h (the motion sensor -
// Otto's inner ear). Zero overhead. Requires
// config.mpu6050.enabled = true.
//================================================================
#pragma once
#include "../modules/Mpu6050.h"

namespace Balance {
  /** @return forward/back tilt in degrees (0 = upright). */
  inline float pitchDegrees() { return Mpu6050::pitchDegrees(); }
  /** @return left/right tilt in degrees (0 = upright). */
  inline float rollDegrees()  { return Mpu6050::rollDegrees(); }

  /** @return true when the robot is upright within @p toleranceDegrees of level. */
  inline bool isLevelWithinDegrees(float toleranceDegrees = 15) {
    return Mpu6050::isLevelWithinDegrees(toleranceDegrees);
  }
  /** @return true when the robot is flipped over. */
  inline bool isUpsideDown() { return Mpu6050::isUpsideDown(); }
  /** @return true when acceleration exceeds @p thresholdG (a shake). */
  inline bool isShakenHarderThanG(float thresholdG = 0.6) {
    return Mpu6050::isShakenHarderThanG(thresholdG);
  }
}
