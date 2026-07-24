//================================================================
// OttoFlow - core/Icons.h
// Named icons for the 8x8 LED matrix. These map to the 31 built-in
// OttoDIYLib mouth shapes; digits 0-9 are shown via
// Mouth::showDigit() / Matrix::drawDigit().
//================================================================
#pragma once
#include <Arduino.h>

enum class Icon : uint8_t {
  Heart,
  Happy,          // open smile
  HappyClosed,
  Smile,
  Sad,
  SadOpen,
  SadClosed,
  Angry,
  Surprised,      // big surprise
  SmallSurprise,
  Confused,
  TongueOut,
  Vampire1,
  Vampire2,
  Line,           // neutral straight mouth
  Diagonal,
  Ok,
  X,
  Question,       // interrogation mark
  Thunder,
  Culito
};
