//================================================================
// OttoFlow - modules/Buzzer.h
// The piezo buzzer. Named songs, raw tones, and a global mute -
// while muted every sound call is a silent no-op.
//================================================================
#pragma once
#include <Arduino.h>
#include "../core/Sounds.h"

namespace Buzzer {
  /** Play a named sound effect (see the Sound enum). */
  void play(Sound sound);
  /** Play a tone at @p frequencyHz for @p durationMs, then @p silenceAfterMs of quiet. */
  void playToneHz(float frequencyHz, long durationMs, int silenceAfterMs = 0);
  /**
   * Sweep from @p startHz to @p endHz in @p step multipliers, playing each
   * note for @p noteDurationMs with @p silenceBetweenMs between them.
   */
  void bendTonesHz(float startHz, float endHz, float step,
                   long noteDurationMs, int silenceBetweenMs);

  /** Silence the buzzer; subsequent sound calls become no-ops. */
  void mute();
  /** Allow the buzzer to sound again after mute(). */
  void unmute();
  /** @return true while the buzzer is muted. */
  bool isMuted();
}
