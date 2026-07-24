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
  // Called by OttoFlow::start() when enabled; safe to call again.
  // Returns false when the sensor does not answer on the bus.
  bool begin();
  bool isConnected();

  //-- Raw motion data
  // Acceleration in g (1.0 = earth gravity), per axis.
  void readAccelerationG(float& x, float& y, float& z);
  // Rotation rate in degrees per second, per axis.
  void readRotationDps(float& x, float& y, float& z);
  // Die temperature in Celsius (the chip has a thermometer).
  float temperatureC();

  //-- Orientation (computed from gravity; valid when not moving fast)
  float pitchDegrees();   // nose up/down,  0 = level
  float rollDegrees();    // lean left/right, 0 = level

  //-- Convenience checks
  bool isLevelWithinDegrees(float toleranceDegrees = 15);
  bool isUpsideDown();
  // True when current total acceleration deviates from 1 g by more
  // than the threshold - a shake, bump, or being picked up.
  bool isShakenHarderThanG(float thresholdG = 0.6);
}
