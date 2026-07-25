//================================================================
// OttoFlow - facades/Arms.h
// Expressive layer over modules/ArmServos.h. Only active when
// arms are enabled (Preset::Humanoid or config.arms.enabled);
// otherwise every call is a silent no-op.
//================================================================
#pragma once
#include "../modules/ArmServos.h"

namespace Arms {
  /** Raise both arms to @p degrees (0..180, default 160). */
  inline void raiseBoth(uint8_t degrees = 160)  { ArmServos::positionBothDegrees(degrees); }
  /** Lower both arms to @p degrees (0..180, default 20). */
  inline void lowerBoth(uint8_t degrees = 20)   { ArmServos::positionBothDegrees(degrees); }
  /** Move the left arm to @p degrees (0..180, default 160). */
  inline void raiseLeft(uint8_t degrees = 160)  { ArmServos::positionLeftDegrees(degrees); }
  /** Move the right arm to @p degrees (0..180, default 160). */
  inline void raiseRight(uint8_t degrees = 160) { ArmServos::positionRightDegrees(degrees); }
  /** Wave the right arm @p times (blocking greeting motion). */
  inline void waveRight(uint8_t times = 2)      { ArmServos::waveRight(times); }
  /** Wave the left arm @p times (blocking greeting motion). */
  inline void waveLeft(uint8_t times = 2)       { ArmServos::waveLeft(times); }
  /** Return both arms to the center rest position (90 deg). */
  inline void home()                            { ArmServos::positionBothDegrees(90); }

  /** Detach the arm servos so they stop drawing power and go limp. */
  inline void relax()      { ArmServos::detach(); }
  /** Re-attach the arm servos after relax() so they hold position again. */
  inline void hold()       { ArmServos::attach(); }
  /** @return true while the arm servos are attached and driven. */
  inline bool isActive()   { return ArmServos::isAttached(); }
}
