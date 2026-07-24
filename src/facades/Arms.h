//================================================================
// OttoFlow - facades/Arms.h
// Expressive layer over modules/ArmServos.h. Only active when
// arms are enabled (Preset::Humanoid or config.arms.enabled);
// otherwise every call is a silent no-op.
//================================================================
#pragma once
#include "../modules/ArmServos.h"

namespace Arms {
  inline void raiseBoth(uint8_t degrees = 160)  { ArmServos::positionBothDegrees(degrees); }
  inline void lowerBoth(uint8_t degrees = 20)   { ArmServos::positionBothDegrees(degrees); }
  inline void raiseLeft(uint8_t degrees = 160)  { ArmServos::positionLeftDegrees(degrees); }
  inline void raiseRight(uint8_t degrees = 160) { ArmServos::positionRightDegrees(degrees); }
  inline void waveRight(uint8_t times = 2)      { ArmServos::waveRight(times); }
  inline void waveLeft(uint8_t times = 2)       { ArmServos::waveLeft(times); }

  inline void relax()      { ArmServos::detach(); }   // stop driving the servos
  inline void hold()       { ArmServos::attach(); }   // drive them again
  inline bool isActive()   { return ArmServos::isAttached(); }
}
