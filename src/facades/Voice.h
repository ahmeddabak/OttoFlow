//================================================================
// OttoFlow - facades/Voice.h
// Expressive layer over modules/Buzzer.h. Zero overhead: every
// call inlines straight to the module underneath.
//================================================================
#pragma once
#include "../modules/Buzzer.h"

namespace Voice {
  inline void play(Sound sound) { Buzzer::play(sound); }
  inline void playToneHz(float frequencyHz, long durationMs, int silenceAfterMs = 0) {
    Buzzer::playToneHz(frequencyHz, durationMs, silenceAfterMs);
  }

  inline void mute()    { Buzzer::mute(); }
  inline void unmute()  { Buzzer::unmute(); }
  inline bool isMuted() { return Buzzer::isMuted(); }
}
