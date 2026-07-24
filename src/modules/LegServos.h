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
  void enable();      // attach servos, allow movement
  void disable();     // detach servos, ignore all movement calls
  bool isEnabled();

  void home();        // rest position

  //-- Locomotion
  void walk(float steps, int periodMs, int dir);
  void turn(float steps, int periodMs, int dir);
  void bend(int steps, int periodMs, int dir);
  void shakeLeg(int steps, int periodMs, int dir);
  void jump(float steps = 1, int periodMs = 2000);

  //-- Dance moves (amplitude = size of the movement in degrees)
  void upDown(float cycles, int periodMs, int amplitude);
  void swing(float cycles, int periodMs, int amplitude);
  void tiptoeSwing(float cycles, int periodMs, int amplitude);
  void jitter(float cycles, int periodMs, int amplitude);
  void ascendingTurn(float cycles, int periodMs, int amplitude);
  void moonwalk(float cycles, int periodMs, int amplitude, int dir);
  void crusaito(float cycles, int periodMs, int amplitude, int dir);
  void flap(float cycles, int periodMs, int amplitude, int dir);

  //-- Direct single-servo control (angles 0..180, 90 = center).
  //-- Instant move; respects the disable() guard like everything else.
  void positionLegLeftDegrees(uint8_t angle);
  void positionLegRightDegrees(uint8_t angle);
  void positionFootLeftDegrees(uint8_t angle);
  void positionFootRightDegrees(uint8_t angle);

  //-- Move all four servos together, smoothly interpolated over
  //-- durationMs (like a keyframe).
  void positionAllDegrees(uint8_t legLeft, uint8_t legRight,
                          uint8_t footLeft, uint8_t footRight,
                          int durationMs = 200);

  //-- Whole-body gestures (movement + mouth + sound combined)
  void playGesture(Gesture gesture);

  //-- Servo calibration
  void setTrimsDegrees(int legLeft, int legRight, int footLeft, int footRight);
  void saveTrimsToEeprom();   // loaded automatically at start (see OttoConfig)
}
