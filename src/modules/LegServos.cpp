#include "LegServos.h"
#include "../core/Internal.h"
#include <Otto.h>

using ottoflow_internal::drv;

namespace LegServos {

static bool s_enabled = true;

void enable() {
  if (!s_enabled) {
    drv().attachServos();
    s_enabled = true;
  }
}

void disable() {
  if (s_enabled) {
    drv().detachServos();
    s_enabled = false;
  }
}

bool isEnabled() { return s_enabled; }

// Every movement goes through this guard.
#define GUARDED(call) do { if (s_enabled) { drv().call; } } while (0)

void center() { GUARDED(home()); }

void walk(float steps, int periodMs, int dir)     { GUARDED(walk(steps, periodMs, dir)); }
void turn(float steps, int periodMs, int dir)     { GUARDED(turn(steps, periodMs, dir)); }
void bend(int steps, int periodMs, int dir)       { GUARDED(bend(steps, periodMs, dir)); }
void shakeLeg(int steps, int periodMs, int dir)   { GUARDED(shakeLeg(steps, periodMs, dir)); }
void jump(float steps, int periodMs)              { GUARDED(jump(steps, periodMs)); }

void upDown(float cycles, int periodMs, int amplitude)        { GUARDED(updown(cycles, periodMs, amplitude)); }
void swing(float cycles, int periodMs, int amplitude)         { GUARDED(swing(cycles, periodMs, amplitude)); }
void tiptoeSwing(float cycles, int periodMs, int amplitude)   { GUARDED(tiptoeSwing(cycles, periodMs, amplitude)); }
void jitter(float cycles, int periodMs, int amplitude)        { GUARDED(jitter(cycles, periodMs, amplitude)); }
void ascendingTurn(float cycles, int periodMs, int amplitude) { GUARDED(ascendingTurn(cycles, periodMs, amplitude)); }

void moonwalk(float cycles, int periodMs, int amplitude, int dir) { GUARDED(moonwalker(cycles, periodMs, amplitude, dir)); }
void crusaito(float cycles, int periodMs, int amplitude, int dir) { GUARDED(crusaito(cycles, periodMs, amplitude, dir)); }
void flap(float cycles, int periodMs, int amplitude, int dir)     { GUARDED(flapping(cycles, periodMs, amplitude, dir)); }

// OttoDIYLib servo indices: 0 = leg left, 1 = leg right,
//                           2 = foot left, 3 = foot right
void positionLegLeftDegrees(uint8_t angle)   { GUARDED(_moveSingle(angle, 0)); }
void positionLegRightDegrees(uint8_t angle)  { GUARDED(_moveSingle(angle, 1)); }
void positionFootLeftDegrees(uint8_t angle)  { GUARDED(_moveSingle(angle, 2)); }
void positionFootRightDegrees(uint8_t angle) { GUARDED(_moveSingle(angle, 3)); }

void positionAllDegrees(uint8_t legLeft, uint8_t legRight,
                        uint8_t footLeft, uint8_t footRight, int durationMs) {
  if (!s_enabled) return;
  int targets[4] = {legLeft, legRight, footLeft, footRight};
  drv()._moveServos(durationMs, targets);
}

// Map the framework's Gesture enum to OttoDIYLib gesture ids.
static int gestureIdFor(Gesture gesture) {
  switch (gesture) {
    case Gesture::Happy:      return OttoHappy;
    case Gesture::SuperHappy: return OttoSuperHappy;
    case Gesture::Sad:        return OttoSad;
    case Gesture::Sleeping:   return OttoSleeping;
    case Gesture::Fart:       return OttoFart;
    case Gesture::Confused:   return OttoConfused;
    case Gesture::Love:       return OttoLove;
    case Gesture::Angry:      return OttoAngry;
    case Gesture::Fretful:    return OttoFretful;
    case Gesture::Magic:      return OttoMagic;
    case Gesture::Wave:       return OttoWave;
    case Gesture::Victory:    return OttoVictory;
    case Gesture::Fail:       return OttoFail;
  }
  return OttoHappy;  // unreachable, keeps the compiler happy
}

void playGesture(Gesture gesture) { GUARDED(playGesture(gestureIdFor(gesture))); }

#undef GUARDED

void setTrimsDegrees(int legLeft, int legRight, int footLeft, int footRight) {
  drv().setTrims(legLeft, legRight, footLeft, footRight);
}

void saveTrimsToEeprom() { drv().saveTrimsOnEEPROM(); }

}  // namespace LegServos
