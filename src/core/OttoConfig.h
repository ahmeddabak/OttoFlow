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
enum class Preset : uint8_t {
  Biped,      // classic Otto: 4 servos, no arms (default)
  Humanoid    // Otto Humanoid: + 2 arm servos on pins 6 (left) / 7 (right)
};

//-- Per-module configuration ---------------------------------------
struct LegServoPins {
  uint8_t legLeft   = 2;
  uint8_t legRight  = 3;
  uint8_t footLeft  = 4;
  uint8_t footRight = 5;
};

struct ArmsConfig {
  bool    enabled  = false;   // off by default; Preset::Humanoid turns it on
  uint8_t leftPin  = 6;
  uint8_t rightPin = 7;
};

struct MatrixConfig {
  uint8_t din         = A3;
  uint8_t cs          = A2;
  uint8_t clk         = A1;
  uint8_t orientation = 1;    // Top = 1, Bottom = 2, Left = 3, Right = 4
  uint8_t brightness  = 4;    // 0 (dim) .. 15 (bright)
};

struct UltrasonicConfig {
  uint8_t  triggerPin     = 8;
  uint8_t  echoPin        = 9;
  bool     medianFilter   = true;  // median of `samples` readings kills HC-SR04 spikes
  uint8_t  samples        = 3;     // 1..5 readings per distanceCm() call
  uint16_t timeoutMicros  = 25000; // per reading (~4 m round trip)
};

struct BuzzerConfig {
  uint8_t pin          = 13;
  bool    muted        = false;  // start muted (Voice::mute() also works at runtime)
  bool    helloOnStart = true;   // chirp once when OttoFlow::start() finishes
};

//-- The whole robot ------------------------------------------------
struct OttoConfig {
  LegServoPins     legs;
  ArmsConfig       arms;
  MatrixConfig     matrix;
  UltrasonicConfig ultrasonic;
  BuzzerConfig     buzzer;
  bool loadTrimsFromEeprom = true;  // servo calibration saved by Legs::saveTrimsToEeprom()

  OttoConfig() = default;

  // Allows `OttoConfig cfg = Preset::Humanoid;`
  OttoConfig(Preset preset) {
    if (preset == Preset::Humanoid) {
      arms.enabled = true;
    }
  }
};
