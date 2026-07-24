//================================================================
// OttoFlow - facades/Gestures.h
// Whole-body gestures: movement + face + sound in one call.
// Note: gestures move the legs, so they respect Legs::disable().
//================================================================
#pragma once
#include "../modules/LegServos.h"

namespace Gestures {
  inline void play(Gesture gesture) { LegServos::playGesture(gesture); }
}
