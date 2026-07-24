#include "Mpu6050.h"
#include "../core/Internal.h"
#include <Wire.h>
#include <math.h>

using ottoflow_internal::config;

namespace Mpu6050 {

// MPU-6050 register map (the few we need)
static const uint8_t REG_PWR_MGMT_1  = 0x6B;
static const uint8_t REG_ACCEL_XOUT  = 0x3B;  // 14 bytes: accel, temp, gyro

static bool s_connected = false;

static uint8_t address() { return config().mpu6050.i2cAddress; }

bool begin() {
  if (!config().mpu6050.enabled) return false;
  Wire.begin();
  Wire.beginTransmission(address());
  Wire.write(REG_PWR_MGMT_1);
  Wire.write(0);                          // wake up (starts in sleep mode)
  s_connected = (Wire.endTransmission() == 0);
  return s_connected;
}

bool isConnected() { return s_connected; }

// Read the full 14-byte sensor block: accelX/Y/Z, temp, gyroX/Y/Z.
static bool readBlock(int16_t values[7]) {
  if (!s_connected) return false;
  Wire.beginTransmission(address());
  Wire.write(REG_ACCEL_XOUT);
  if (Wire.endTransmission(false) != 0) return false;
  if (Wire.requestFrom(address(), (uint8_t)14) != 14) return false;
  for (uint8_t i = 0; i < 7; i++) {
    values[i] = (int16_t)((Wire.read() << 8) | Wire.read());
  }
  return true;
}

void readAccelerationG(float& x, float& y, float& z) {
  int16_t v[7];
  if (!readBlock(v)) { x = y = z = 0; return; }
  x = v[0] / 16384.0f;   // default +/-2 g range
  y = v[1] / 16384.0f;
  z = v[2] / 16384.0f;
}

void readRotationDps(float& x, float& y, float& z) {
  int16_t v[7];
  if (!readBlock(v)) { x = y = z = 0; return; }
  x = v[4] / 131.0f;     // default +/-250 deg/s range
  y = v[5] / 131.0f;
  z = v[6] / 131.0f;
}

float temperatureC() {
  int16_t v[7];
  if (!readBlock(v)) return 0;
  return v[3] / 340.0f + 36.53f;   // datasheet formula
}

float pitchDegrees() {
  float x, y, z;
  readAccelerationG(x, y, z);
  return atan2(-x, sqrt(y * y + z * z)) * 180.0f / (float)M_PI;
}

float rollDegrees() {
  float x, y, z;
  readAccelerationG(x, y, z);
  return atan2(y, z) * 180.0f / (float)M_PI;
}

bool isLevelWithinDegrees(float toleranceDegrees) {
  return fabs(pitchDegrees()) < toleranceDegrees &&
         fabs(rollDegrees())  < toleranceDegrees;
}

bool isUpsideDown() {
  float x, y, z;
  readAccelerationG(x, y, z);
  return z < 0;
}

bool isShakenHarderThanG(float thresholdG) {
  float x, y, z;
  readAccelerationG(x, y, z);
  float magnitude = sqrt(x * x + y * y + z * z);   // 1.0 at rest
  return fabs(magnitude - 1.0f) > thresholdG;
}

}  // namespace Mpu6050
