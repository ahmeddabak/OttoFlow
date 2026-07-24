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
  void attach();      // called by OttoFlow::start() when arms are enabled
  void detach();      // relax: stop driving the arm servos
  bool isAttached();

  void positionLeftDegrees(uint8_t angle);
  void positionRightDegrees(uint8_t angle);
  void positionBothDegrees(uint8_t angle);

  // Simple blocking wave with one arm (demo/greeting motion).
  void waveRight(uint8_t times = 2);
  void waveLeft(uint8_t times = 2);
}
