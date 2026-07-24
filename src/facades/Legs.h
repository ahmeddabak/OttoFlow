//================================================================
// OttoFlow - facades/Legs.h
// Expressive layer over modules/LegServos.h with direction-named calls
// so a sketch never contains a bare 1 / -1. Zero overhead.
//
// All calls are BLOCKING in v1 (they return when the motion ends).
// While Legs::disable() is active every call is a silent no-op.
//================================================================
#pragma once
#include "../modules/LegServos.h"

namespace Legs {
  inline void enable()     { LegServos::enable(); }
  inline void disable()    { LegServos::disable(); }
  inline bool isEnabled()  { return LegServos::isEnabled(); }
  inline void home()       { LegServos::home(); }

  //-- Walking / turning (periodMs: higher = slower, ~600..1400)
  inline void walkForward(float steps, int periodMs = 1000)  { LegServos::walk(steps, periodMs, 1); }
  inline void walkBackward(float steps, int periodMs = 1000) { LegServos::walk(steps, periodMs, -1); }
  inline void turnLeft(float steps, int periodMs = 2000)     { LegServos::turn(steps, periodMs, 1); }
  inline void turnRight(float steps, int periodMs = 2000)    { LegServos::turn(steps, periodMs, -1); }

  //-- Small moves
  inline void bendLeft(int steps = 1, int periodMs = 1400)   { LegServos::bend(steps, periodMs, 1); }
  inline void bendRight(int steps = 1, int periodMs = 1400)  { LegServos::bend(steps, periodMs, -1); }
  inline void shakeLeftLeg(int steps = 1, int periodMs = 2000)  { LegServos::shakeLeg(steps, periodMs, 1); }
  inline void shakeRightLeg(int steps = 1, int periodMs = 2000) { LegServos::shakeLeg(steps, periodMs, -1); }
  inline void jump(float steps = 1, int periodMs = 2000)     { LegServos::jump(steps, periodMs); }

  //-- Dance moves (amplitude = size of the movement in degrees)
  inline void upDown(float cycles = 1, int periodMs = 1000, int amplitude = 20)        { LegServos::upDown(cycles, periodMs, amplitude); }
  inline void swing(float cycles = 1, int periodMs = 1000, int amplitude = 20)         { LegServos::swing(cycles, periodMs, amplitude); }
  inline void tiptoeSwing(float cycles = 1, int periodMs = 900, int amplitude = 20)    { LegServos::tiptoeSwing(cycles, periodMs, amplitude); }
  inline void jitter(float cycles = 1, int periodMs = 500, int amplitude = 20)         { LegServos::jitter(cycles, periodMs, amplitude); }
  inline void ascendingTurn(float cycles = 1, int periodMs = 900, int amplitude = 50)  { LegServos::ascendingTurn(cycles, periodMs, amplitude); }
  inline void moonwalkLeft(float cycles = 1, int periodMs = 900, int amplitude = 25)   { LegServos::moonwalk(cycles, periodMs, amplitude, 1); }
  inline void moonwalkRight(float cycles = 1, int periodMs = 900, int amplitude = 25)  { LegServos::moonwalk(cycles, periodMs, amplitude, -1); }
  inline void crusaitoLeft(float cycles = 1, int periodMs = 900, int amplitude = 20)   { LegServos::crusaito(cycles, periodMs, amplitude, 1); }
  inline void crusaitoRight(float cycles = 1, int periodMs = 900, int amplitude = 20)  { LegServos::crusaito(cycles, periodMs, amplitude, -1); }
  inline void flapForward(float cycles = 1, int periodMs = 1000, int amplitude = 20)   { LegServos::flap(cycles, periodMs, amplitude, 1); }
  inline void flapBackward(float cycles = 1, int periodMs = 1000, int amplitude = 20)  { LegServos::flap(cycles, periodMs, amplitude, -1); }

  //-- Calibration
  inline void setTrimsDegrees(int legLeft, int legRight, int footLeft, int footRight) {
    LegServos::setTrimsDegrees(legLeft, legRight, footLeft, footRight);
  }
  inline void saveTrimsToEeprom() { LegServos::saveTrimsToEeprom(); }
}
