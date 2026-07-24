//================================================================
// OttoFlow - facades/Motion.h
// The all-movement switch: legs AND arms together. This is the
// one call for "the robot must not move" - bench testing, safe
// handling, low power.
//
//   Motion::disable();   // detach every servo, all moves no-op
//   Motion::enable();    // re-attach (arms only if configured)
//
// Legs::disable() / Arms::relax() remain available when you want
// to switch off just one group.
//================================================================
#pragma once
#include "../modules/LegServos.h"
#include "../modules/ArmServos.h"

namespace Motion {
  // Detach ALL servos (legs, feet, and arms if present).
  // Every movement call becomes a silent no-op.
  inline void disable() {
    LegServos::disable();
    ArmServos::detach();
  }

  // Re-attach all servos this build has (arms only when enabled
  // in the configuration).
  inline void enable() {
    LegServos::enable();
    ArmServos::attach();
  }

  // True when any servo group is active.
  inline bool isEnabled() {
    return LegServos::isEnabled() || ArmServos::isAttached();
  }
}
