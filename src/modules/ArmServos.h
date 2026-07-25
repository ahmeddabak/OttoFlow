//================================================================
// OttoFlow - modules/ArmServos.h
// The two optional arm servos (Otto Humanoid build). Disabled by
// default - enable via Preset::Humanoid or config.arms.enabled.
// While disabled (or detached) every call is a silent no-op.
//
// Angles: 0..180 degrees. What "up" means depends on how the arm
// horns are mounted; adjust angles to your build.
//================================================================
#pragma once
#include <Arduino.h>

namespace ArmServos {
  /** Attach the arm servos. Called by OttoFlow::start() when arms are enabled. */
  void attach();
  /** Detach the arm servos (relax): stop driving them so they go limp. */
  void detach();
  /** @return true while the arm servos are attached and driven. */
  bool isAttached();

  /** Move the left arm to @p angle (0..180). */
  void positionLeftDegrees(uint8_t angle);
  /** Move the right arm to @p angle (0..180). */
  void positionRightDegrees(uint8_t angle);
  /** Move both arms to @p angle (0..180). */
  void positionBothDegrees(uint8_t angle);

  /** Blocking wave with the right arm, @p times (demo/greeting motion). */
  void waveRight(uint8_t times = 2);
  /** Blocking wave with the left arm, @p times (demo/greeting motion). */
  void waveLeft(uint8_t times = 2);
}
