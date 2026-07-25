//================================================================
// OttoFlow - modules/Mpu6050.h
// The MPU-6050 6-axis motion sensor (GY-521 board): 3-axis
// accelerometer + 3-axis gyroscope over I2C (Nano: SDA=A4, SCL=A5).
//
// Enable in config before use:
//   OttoConfig cfg;
//   cfg.mpu6050.enabled = true;
//   OttoFlow::start(cfg);
//
// Minimal built-in driver - no external library needed.
//================================================================
#pragma once
#include <Arduino.h>

namespace Mpu6050 {
  /**
   * Initialise the sensor. Called by OttoFlow::start() when enabled;
   * safe to call again.
   * @return false when the sensor does not answer on the I2C bus.
   */
  bool begin();
  /** @return true when the sensor is responding on the I2C bus. */
  bool isConnected();

  //-- Raw motion data

  /** Read acceleration in g (1.0 = earth gravity) into @p x, @p y, @p z. */
  void readAccelerationG(float& x, float& y, float& z);
  /** Read rotation rate in degrees per second into @p x, @p y, @p z. */
  void readRotationDps(float& x, float& y, float& z);
  /** @return die temperature in Celsius (the chip has a thermometer). */
  float temperatureC();

  //-- Orientation (computed from gravity; valid when not moving fast)

  /** @return nose up/down tilt in degrees (0 = level). */
  float pitchDegrees();
  /** @return lean left/right tilt in degrees (0 = level). */
  float rollDegrees();

  //-- Convenience checks

  /** @return true when the robot is upright within @p toleranceDegrees of level. */
  bool isLevelWithinDegrees(float toleranceDegrees = 15);
  /** @return true when the robot is flipped over. */
  bool isUpsideDown();
  /**
   * @return true when total acceleration deviates from 1 g by more than
   * @p thresholdG - a shake, bump, or being picked up.
   */
  bool isShakenHarderThanG(float thresholdG = 0.6);
}
