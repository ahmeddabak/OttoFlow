//================================================================
// OttoFlow - modules/LegServos.h
// The four leg/foot servos: locomotion, dance moves, gestures,
// calibration trims, and a global enable/disable switch.
// (Named symmetrically with ArmServos - see DESIGN.md.)
//
// While disabled the servos are detached (no jitter, no power
// draw) and every movement call is a silent no-op - ideal for
// bench testing other hardware.
//
// All movement calls in v1 are BLOCKING: they return when the
// motion finishes. Non-blocking variants (startWalking/isMoving)
// are on the roadmap - see ROADMAP.md.
//
// Directions: dir = 1 (forward / left), dir = -1 (backward / right)
// periodMs: duration of one movement cycle; higher = slower
//           (useful range roughly 600..1400 for walking)
//================================================================
#pragma once
#include <Arduino.h>
#include "../core/Gestures.h"

namespace LegServos {
  /** Attach the servos and allow movement. */
  void enable();
  /** Detach the servos and ignore all movement calls. */
  void disable();
  /** @return true while the servos are attached and driven. */
  bool isEnabled();

  /** Move all four servos to the center rest position (90 deg). */
  void home();

  //-- Locomotion

  /** Walk @p steps in @p dir (1 = forward, -1 = backward); @p periodMs = one step (higher = slower). */
  void walk(float steps, int periodMs, int dir);
  /** Turn @p steps in @p dir (1 = left, -1 = right); @p periodMs = one step (higher = slower). */
  void turn(float steps, int periodMs, int dir);
  /** Lean the body @p steps in @p dir (1 = left, -1 = right). */
  void bend(int steps, int periodMs, int dir);
  /** Shake a leg @p steps in @p dir (1 = left, -1 = right). */
  void shakeLeg(int steps, int periodMs, int dir);
  /** Hop in place @p steps. */
  void jump(float steps = 1, int periodMs = 2000);

  //-- Dance moves (amplitude = size of the movement in degrees)

  /** Bob up and down for @p cycles; @p amplitude in degrees. */
  void upDown(float cycles, int periodMs, int amplitude);
  /** Sway side to side for @p cycles; @p amplitude in degrees. */
  void swing(float cycles, int periodMs, int amplitude);
  /** Swing up on tiptoes for @p cycles; @p amplitude in degrees. */
  void tiptoeSwing(float cycles, int periodMs, int amplitude);
  /** Quick shivering jitter for @p cycles; @p amplitude in degrees. */
  void jitter(float cycles, int periodMs, int amplitude);
  /** Rising turn for @p cycles; @p amplitude in degrees. */
  void ascendingTurn(float cycles, int periodMs, int amplitude);
  /** Moonwalk for @p cycles in @p dir (1 = left, -1 = right); @p amplitude in degrees. */
  void moonwalk(float cycles, int periodMs, int amplitude, int dir);
  /** Crusaito step for @p cycles in @p dir (1 = left, -1 = right); @p amplitude in degrees. */
  void crusaito(float cycles, int periodMs, int amplitude, int dir);
  /** Flap the feet for @p cycles in @p dir (1 = forward, -1 = backward); @p amplitude in degrees. */
  void flap(float cycles, int periodMs, int amplitude, int dir);

  //-- Direct single-servo control (angles 0..180, 90 = center).
  //-- Instant move; respects the disable() guard like everything else.

  /** Move the left leg (hip) servo to @p angle (0..180, 90 = center). */
  void positionLegLeftDegrees(uint8_t angle);
  /** Move the right leg (hip) servo to @p angle (0..180, 90 = center). */
  void positionLegRightDegrees(uint8_t angle);
  /** Move the left foot (ankle) servo to @p angle (0..180, 90 = center). */
  void positionFootLeftDegrees(uint8_t angle);
  /** Move the right foot (ankle) servo to @p angle (0..180, 90 = center). */
  void positionFootRightDegrees(uint8_t angle);

  /**
   * Move all four servos together, smoothly interpolated over
   * @p durationMs (like a keyframe).
   */
  void positionAllDegrees(uint8_t legLeft, uint8_t legRight,
                          uint8_t footLeft, uint8_t footRight,
                          int durationMs = 200);

  //-- Whole-body gestures (movement + mouth + sound combined)

  /** Play a whole-body gesture combining movement, mouth and sound (see the Gesture enum). */
  void playGesture(Gesture gesture);

  //-- Servo calibration

  /** Set per-servo trim offsets (in degrees) to correct mechanical misalignment. */
  void setTrimsDegrees(int legLeft, int legRight, int footLeft, int footRight);
  /** Persist the current trims to EEPROM (loaded automatically at start; see OttoConfig). */
  void saveTrimsToEeprom();
}
