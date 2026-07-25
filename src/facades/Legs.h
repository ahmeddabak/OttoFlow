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
  /** Attach the leg/foot servos and allow movement. */
  inline void enable()     { LegServos::enable(); }
  /** Detach the leg/foot servos; every movement call becomes a no-op. */
  inline void disable()    { LegServos::disable(); }
  /** @return true while the leg/foot servos are attached and driven. */
  inline bool isEnabled()  { return LegServos::isEnabled(); }
  /** Return all four leg/foot servos to the center rest position (90 deg). */
  inline void home()       { LegServos::home(); }

  //-- Walking / turning (periodMs: higher = slower, ~600..1400)

  /** Walk forward @p steps. @p periodMs is one step's duration (higher = slower). */
  inline void walkForward(float steps, int periodMs = 1000)  { LegServos::walk(steps, periodMs, 1); }
  /** Walk backward @p steps. @p periodMs is one step's duration (higher = slower). */
  inline void walkBackward(float steps, int periodMs = 1000) { LegServos::walk(steps, periodMs, -1); }
  /** Turn left in place @p steps. @p periodMs is one step's duration (higher = slower). */
  inline void turnLeft(float steps, int periodMs = 2000)     { LegServos::turn(steps, periodMs, 1); }
  /** Turn right in place @p steps. @p periodMs is one step's duration (higher = slower). */
  inline void turnRight(float steps, int periodMs = 2000)    { LegServos::turn(steps, periodMs, -1); }

  //-- Small moves

  /** Lean the body left @p steps. */
  inline void bendLeft(int steps = 1, int periodMs = 1400)   { LegServos::bend(steps, periodMs, 1); }
  /** Lean the body right @p steps. */
  inline void bendRight(int steps = 1, int periodMs = 1400)  { LegServos::bend(steps, periodMs, -1); }
  /** Shake the left leg @p steps. */
  inline void shakeLeftLeg(int steps = 1, int periodMs = 2000)  { LegServos::shakeLeg(steps, periodMs, 1); }
  /** Shake the right leg @p steps. */
  inline void shakeRightLeg(int steps = 1, int periodMs = 2000) { LegServos::shakeLeg(steps, periodMs, -1); }
  /** Hop in place @p steps. */
  inline void jump(float steps = 1, int periodMs = 2000)     { LegServos::jump(steps, periodMs); }

  //-- Dance moves (amplitude = size of the movement in degrees)

  /** Bob up and down for @p cycles. @p amplitude is the move size in degrees. */
  inline void upDown(float cycles = 1, int periodMs = 1000, int amplitude = 20)        { LegServos::upDown(cycles, periodMs, amplitude); }
  /** Sway side to side for @p cycles. @p amplitude is the move size in degrees. */
  inline void swing(float cycles = 1, int periodMs = 1000, int amplitude = 20)         { LegServos::swing(cycles, periodMs, amplitude); }
  /** Swing up on tiptoes for @p cycles. @p amplitude is the move size in degrees. */
  inline void tiptoeSwing(float cycles = 1, int periodMs = 900, int amplitude = 20)    { LegServos::tiptoeSwing(cycles, periodMs, amplitude); }
  /** Quick shivering jitter for @p cycles. @p amplitude is the move size in degrees. */
  inline void jitter(float cycles = 1, int periodMs = 500, int amplitude = 20)         { LegServos::jitter(cycles, periodMs, amplitude); }
  /** Rising turn for @p cycles. @p amplitude is the move size in degrees. */
  inline void ascendingTurn(float cycles = 1, int periodMs = 900, int amplitude = 50)  { LegServos::ascendingTurn(cycles, periodMs, amplitude); }
  /** Moonwalk drifting left for @p cycles. @p amplitude is the move size in degrees. */
  inline void moonwalkLeft(float cycles = 1, int periodMs = 900, int amplitude = 25)   { LegServos::moonwalk(cycles, periodMs, amplitude, 1); }
  /** Moonwalk drifting right for @p cycles. @p amplitude is the move size in degrees. */
  inline void moonwalkRight(float cycles = 1, int periodMs = 900, int amplitude = 25)  { LegServos::moonwalk(cycles, periodMs, amplitude, -1); }
  /** Crusaito step leaning left for @p cycles. @p amplitude is the move size in degrees. */
  inline void crusaitoLeft(float cycles = 1, int periodMs = 900, int amplitude = 20)   { LegServos::crusaito(cycles, periodMs, amplitude, 1); }
  /** Crusaito step leaning right for @p cycles. @p amplitude is the move size in degrees. */
  inline void crusaitoRight(float cycles = 1, int periodMs = 900, int amplitude = 20)  { LegServos::crusaito(cycles, periodMs, amplitude, -1); }
  /** Flap the feet forward for @p cycles. @p amplitude is the move size in degrees. */
  inline void flapForward(float cycles = 1, int periodMs = 1000, int amplitude = 20)   { LegServos::flap(cycles, periodMs, amplitude, 1); }
  /** Flap the feet backward for @p cycles. @p amplitude is the move size in degrees. */
  inline void flapBackward(float cycles = 1, int periodMs = 1000, int amplitude = 20)  { LegServos::flap(cycles, periodMs, amplitude, -1); }

  //-- Direct single-servo control (angles 0..180, 90 = center)

  /** Move the left leg (hip) servo to @p angle (0..180, 90 = center). */
  inline void positionLegLeftDegrees(uint8_t angle)   { LegServos::positionLegLeftDegrees(angle); }
  /** Move the right leg (hip) servo to @p angle (0..180, 90 = center). */
  inline void positionLegRightDegrees(uint8_t angle)  { LegServos::positionLegRightDegrees(angle); }
  /** Move the left foot (ankle) servo to @p angle (0..180, 90 = center). */
  inline void positionFootLeftDegrees(uint8_t angle)  { LegServos::positionFootLeftDegrees(angle); }
  /** Move the right foot (ankle) servo to @p angle (0..180, 90 = center). */
  inline void positionFootRightDegrees(uint8_t angle) { LegServos::positionFootRightDegrees(angle); }
  /** Smoothly move all four servos to a target pose over @p durationMs (a keyframe). */
  inline void positionAllDegrees(uint8_t legLeft, uint8_t legRight,
                                 uint8_t footLeft, uint8_t footRight,
                                 int durationMs = 200) {
    LegServos::positionAllDegrees(legLeft, legRight, footLeft, footRight, durationMs);
  }

  //-- Calibration

  /** Set per-servo trim offsets (in degrees) to correct mechanical misalignment. */
  inline void setTrimsDegrees(int legLeft, int legRight, int footLeft, int footRight) {
    LegServos::setTrimsDegrees(legLeft, legRight, footLeft, footRight);
  }
  /** Persist the current trims to EEPROM so they load automatically at start. */
  inline void saveTrimsToEeprom() { LegServos::saveTrimsToEeprom(); }
}
