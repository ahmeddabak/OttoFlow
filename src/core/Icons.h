//================================================================
// OttoFlow - core/Icons.h
// Named icons for the 8x8 LED matrix. These map to the 31 built-in
// OttoDIYLib mouth shapes; digits 0-9 are shown via
// Mouth::showDigit() / Matrix::drawDigit().
//================================================================
#pragma once
#include <Arduino.h>

/** Named expressions for the LED matrix (see Mouth::show / Matrix::drawIcon). */
enum class Icon : uint8_t {
  Heart,
  Happy,          ///< open smile
  HappyClosed,
  Smile,
  Sad,
  SadOpen,
  SadClosed,
  Angry,
  Surprised,      ///< big surprise
  SmallSurprise,
  Confused,
  TongueOut,
  Vampire1,
  Vampire2,
  Line,           ///< neutral straight mouth
  Diagonal,
  Ok,
  X,
  Question,       ///< interrogation mark
  Thunder,
  Culito
};

//-- Your own 8x8 icons ---------------------------------------------
/**
 * An 8x8 icon of your own, stored in flash. One byte per row, top row
 * first; the most significant bit is the leftmost pixel. Define one
 * with OTTOFLOW_ICON and show it with Mouth::showCustom().
 */
struct CustomIcon {
  uint8_t rows[8];
};

/**
 * Define an 8x8 icon in flash (PROGMEM), so it costs no RAM:
 * @code
 *   OTTOFLOW_ICON(Alien,
 *     0b00111100,
 *     0b01111110,
 *     0b11011011,
 *     0b11111111,
 *     0b01011010,
 *     0b10000001,
 *     0b01000010,
 *     0b00100100);
 *   Mouth::showCustom(Alien);
 * @endcode
 * Rows are listed top to bottom; within a row, the leftmost pixel is
 * the highest bit, so the icon reads on screen exactly as written.
 */
#define OTTOFLOW_ICON(name, r0, r1, r2, r3, r4, r5, r6, r7) \
  const CustomIcon name PROGMEM = {{ r0, r1, r2, r3, r4, r5, r6, r7 }}
