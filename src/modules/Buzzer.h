//================================================================
// OttoFlow - modules/Buzzer.h
// The piezo buzzer. Named songs, raw tones, and a global mute -
// while muted every sound call is a silent no-op.
//================================================================
#pragma once
#include <Arduino.h>
#include "../core/Sounds.h"

namespace Buzzer {
  void play(Sound sound);
  void playToneHz(float frequencyHz, long durationMs, int silenceAfterMs = 0);
  void bendTonesHz(float startHz, float endHz, float step,
                   long noteDurationMs, int silenceBetweenMs);

  void mute();
  void unmute();
  bool isMuted();
}
