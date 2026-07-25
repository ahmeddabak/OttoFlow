//================================================================
// OttoFlow - facades/Voice.h
// Expressive layer over modules/Buzzer.h. Zero overhead: every
// call inlines straight to the module underneath.
//================================================================
#pragma once
#include "../modules/Buzzer.h"
#include "../modules/Melody.h"

namespace Voice {
  /** Play a built-in sound effect (see the Sound enum). */
  inline void play(Sound sound) { Buzzer::play(sound); }
  /** Play a single tone at @p frequencyHz for @p durationMs, then @p silenceAfterMs of quiet. */
  inline void playToneHz(float frequencyHz, long durationMs, int silenceAfterMs = 0) {
    Buzzer::playToneHz(frequencyHz, durationMs, silenceAfterMs);
  }

  /** Play a melody from parallel note/beat tables. @p tempoMs is one beat's duration. */
  inline void playMelodyHz(const uint16_t* notesHz, const uint8_t* beats,
                           uint8_t noteCount, uint16_t tempoMs) {
    Melody::playHz(notesHz, beats, noteCount, tempoMs);
  }
  /** Play the built-in "Happy Birthday" tune. */
  inline void playHappyBirthday() { Melody::playHappyBirthday(); }

  /** Silence the buzzer; subsequent play calls produce no sound. */
  inline void mute()    { Buzzer::mute(); }
  /** Allow the buzzer to sound again after mute(). */
  inline void unmute()  { Buzzer::unmute(); }
  /** @return true while the buzzer is muted. */
  inline bool isMuted() { return Buzzer::isMuted(); }
}
