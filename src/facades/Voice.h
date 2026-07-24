//================================================================
// OttoFlow - facades/Voice.h
// Expressive layer over modules/Buzzer.h. Zero overhead: every
// call inlines straight to the module underneath.
//================================================================
#pragma once
#include "../modules/Buzzer.h"
#include "../modules/Melody.h"

namespace Voice {
  inline void play(Sound sound) { Buzzer::play(sound); }
  inline void playToneHz(float frequencyHz, long durationMs, int silenceAfterMs = 0) {
    Buzzer::playToneHz(frequencyHz, durationMs, silenceAfterMs);
  }

  inline void playMelodyHz(const uint16_t* notesHz, const uint8_t* beats,
                           uint8_t noteCount, uint16_t tempoMs) {
    Melody::playHz(notesHz, beats, noteCount, tempoMs);
  }
  inline void playHappyBirthday() { Melody::playHappyBirthday(); }

  inline void mute()    { Buzzer::mute(); }
  inline void unmute()  { Buzzer::unmute(); }
  inline bool isMuted() { return Buzzer::isMuted(); }
}
