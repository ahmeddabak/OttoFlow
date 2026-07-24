#include "Buzzer.h"
#include "../core/Internal.h"
#include <Otto.h>

using ottoflow_internal::drv;
using ottoflow_internal::config;

namespace Buzzer {

// Map the framework's Sound enum to OttoDIYLib song ids.
static int songIdFor(Sound sound) {
  switch (sound) {
    case Sound::Hello:        return S_connection;
    case Sound::Goodbye:      return S_disconnection;
    case Sound::ButtonPushed: return S_buttonPushed;
    case Sound::Mode1:        return S_mode1;
    case Sound::Mode2:        return S_mode2;
    case Sound::Mode3:        return S_mode3;
    case Sound::Surprise:     return S_surprise;
    case Sound::OhOoh:        return S_OhOoh;
    case Sound::OhOoh2:       return S_OhOoh2;
    case Sound::Cuddly:       return S_cuddly;
    case Sound::Sleeping:     return S_sleeping;
    case Sound::Happy:        return S_happy;
    case Sound::SuperHappy:   return S_superHappy;
    case Sound::HappyShort:   return S_happy_short;
    case Sound::Sad:          return S_sad;
    case Sound::Confused:     return S_confused;
    case Sound::Fart1:        return S_fart1;
    case Sound::Fart2:        return S_fart2;
    case Sound::Fart3:        return S_fart3;
  }
  return S_connection;  // unreachable, keeps the compiler happy
}

void play(Sound sound) {
  if (!config().buzzer.muted) drv().sing(songIdFor(sound));
}

void playToneHz(float frequencyHz, long durationMs, int silenceAfterMs) {
  if (!config().buzzer.muted) drv()._tone(frequencyHz, durationMs, silenceAfterMs);
}

void bendTonesHz(float startHz, float endHz, float step,
                 long noteDurationMs, int silenceBetweenMs) {
  if (!config().buzzer.muted) {
    drv().bendTones(startHz, endHz, step, noteDurationMs, silenceBetweenMs);
  }
}

void mute()    { config().buzzer.muted = true; }
void unmute()  { config().buzzer.muted = false; }
bool isMuted() { return config().buzzer.muted; }

}  // namespace Buzzer
