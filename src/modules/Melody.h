//================================================================
// OttoFlow - modules/Melody.h
// Play tunes on the buzzer from note tables, like the official
// Otto_happybirthday example. Respects Voice::mute().
//
//   static const uint16_t NOTES[] PROGMEM = {392, 392, 440, 392};
//   static const uint8_t  BEATS[] PROGMEM = {1, 1, 2, 4};
//   Melody::playHz(NOTES, BEATS, 4, 150);
//
// A note frequency of 0 is a rest (silence for that beat).
//================================================================
#pragma once
#include <Arduino.h>

namespace Melody {
  // Play a melody: parallel PROGMEM tables of note frequencies (Hz)
  // and beat lengths. tempoMs is the duration of one beat.
  void playHz(const uint16_t* notesHz, const uint8_t* beats,
              uint8_t noteCount, uint16_t tempoMs);

  // Built-in tune, matching the official example.
  void playHappyBirthday();
}
