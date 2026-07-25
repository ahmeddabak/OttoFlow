//================================================================
// OttoFlow - core/OttoConfig.h
// Zero-config defaults for the standard Otto DIY kit, presets for
// known builds, and granular override of every pin and setting.
//
//   OttoFlow::start();                       // classic biped kit
//   OttoFlow::start(Preset::Humanoid);       // biped + arms on 6/7
//
//   OttoConfig cfg = Preset::Humanoid;       // power user:
//   cfg.arms.leftPin = 10;                   // override anything
//   OttoFlow::start(cfg);
//================================================================
#pragma once
#include <Arduino.h>

//-- Known kit presets ----------------------------------------------
/** A known Otto build; sets sensible defaults for that kit. */
enum class Preset : uint8_t {
  Biped,      ///< classic Otto: 4 servos, no arms (default)
  Humanoid    ///< Otto Humanoid: + 2 arm servos on pins 6 (left) / 7 (right)
};

//-- Per-module configuration ---------------------------------------
/** Pins for the four leg/foot servos. */
struct LegServoPins {
  uint8_t legLeft   = 2;
  uint8_t legRight  = 3;
  uint8_t footLeft  = 4;
  uint8_t footRight = 5;
};

/** Optional arm servos (Humanoid build). */
struct ArmsConfig {
  bool    enabled  = false;   ///< off by default; Preset::Humanoid turns it on
  uint8_t leftPin  = 6;       ///< left arm servo pin
  uint8_t rightPin = 7;       ///< right arm servo pin
};

/** The 8x8 MAX7219 LED matrix (the mouth). */
struct MatrixConfig {
  uint8_t din         = A3;   ///< data-in pin
  uint8_t cs          = A2;   ///< chip-select pin
  uint8_t clk         = A1;   ///< clock pin
  uint8_t orientation = 1;    ///< Top = 1, Bottom = 2, Left = 3, Right = 4
  uint8_t brightness  = 4;    ///< 0 (dim) .. 15 (bright)
};

/** The HC-SR04 distance sensor (the eyes). */
struct UltrasonicConfig {
  uint8_t  triggerPin     = 8;
  uint8_t  echoPin        = 9;
  bool     medianFilter   = true;  ///< median of `samples` readings kills HC-SR04 spikes
  uint8_t  samples        = 3;     ///< 1..5 readings per distanceCm() call
  uint16_t timeoutMicros  = 25000; ///< per reading (~4 m round trip)
};

/** The piezo buzzer (the voice). */
struct BuzzerConfig {
  uint8_t pin          = 13;
  bool    muted        = false;  ///< start muted (Voice::mute() also works at runtime)
  bool    helloOnStart = true;   ///< chirp once when OttoFlow::start() finishes
};

/** The TTP223 touch sensor (or a push button). */
struct TouchConfig {
  uint8_t pin        = A0;       ///< TTP223 touch sensor (or push button) signal pin
  /**
   * false: output HIGH only while touched (default).
   * true:  output flips on every touch (some kits ship the sensor
   *        soldered this way). wasTapped() works in either mode.
   */
  bool    toggleMode = false;
};

/** The analog microphone / sound sensor (the ears). */
struct SoundSensorConfig {
  uint8_t pin = A6;              ///< analog microphone/sound sensor output
};

/** The photoresistor (LDR) light sensor. */
struct LightSensorConfig {
  /**
   * Photoresistor (LDR) analog output pin. The official single-sensor
   * examples use A0 - change this if you wired it there.
   */
  uint8_t pin = A7;
};

/** Serial Bluetooth module (HC-05/06 or BLE serial). */
struct BluetoothConfig {
  bool     enabled = false;      ///< needs the module wired before enabling
  uint8_t  rxPin   = 11;         ///< board receives here <- module TXD
  uint8_t  txPin   = 12;         ///< board sends here    -> module RXD
  uint16_t baud    = 9600;       ///< standard for HC-05/06 and BLE serial modules
};

/** The MPU-6050 6-axis motion sensor (the inner ear). */
struct Mpu6050Config {
  bool    enabled    = false;    ///< 6-axis accel/gyro on I2C (Nano: SDA=A4, SCL=A5)
  uint8_t i2cAddress = 0x68;     ///< 0x69 when the AD0 pin is pulled high
};

//-- The whole robot ------------------------------------------------
/** Full robot configuration: every module's pins and settings in one place. */
struct OttoConfig {
  LegServoPins      legs;         ///< leg/foot servo pins
  ArmsConfig        arms;         ///< optional arm servos
  MatrixConfig      matrix;       ///< LED matrix (mouth)
  UltrasonicConfig  ultrasonic;   ///< distance sensor (eyes)
  BuzzerConfig      buzzer;       ///< buzzer (voice)
  TouchConfig       touch;        ///< touch sensor
  SoundSensorConfig soundSensor;  ///< microphone (ears)
  LightSensorConfig lightSensor;  ///< photoresistor
  BluetoothConfig   bluetooth;    ///< serial Bluetooth module
  Mpu6050Config     mpu6050;      ///< motion sensor (inner ear)
  bool loadTrimsFromEeprom = true;  ///< load servo trims saved by Legs::saveTrimsToEeprom()

  OttoConfig() = default;

  /** Build a config from a kit @p preset. Allows `OttoConfig cfg = Preset::Humanoid;`. */
  OttoConfig(Preset preset) {
    if (preset == Preset::Humanoid) {
      arms.enabled = true;
    }
  }
};
