//================================================================
// OttoFlow - core/Sounds.h
// Named sounds for the buzzer. These map to the built-in
// OttoDIYLib songs (S_* constants).
//================================================================
#pragma once
#include <Arduino.h>

enum class Sound : uint8_t {
  Hello,          // connection chirp
  Goodbye,        // disconnection
  ButtonPushed,
  Mode1,
  Mode2,
  Mode3,
  Surprise,
  OhOoh,
  OhOoh2,
  Cuddly,
  Sleeping,
  Happy,
  SuperHappy,
  HappyShort,
  Sad,
  Confused,
  Fart1,
  Fart2,
  Fart3
};
