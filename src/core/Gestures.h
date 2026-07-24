//================================================================
// OttoFlow - core/Gestures.h
// Named whole-body gestures (movement + mouth + sound combined).
// These map to the built-in OttoDIYLib gestures (Otto* constants).
//================================================================
#pragma once
#include <Arduino.h>

enum class Gesture : uint8_t {
  Happy,
  SuperHappy,
  Sad,
  Sleeping,
  Fart,
  Confused,
  Love,
  Angry,
  Fretful,
  Magic,
  Wave,
  Victory,
  Fail
};
