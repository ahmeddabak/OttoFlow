//================================================================
// OttoFlow - core/OttoCore.h
// The framework entry point.
//
// Note: the entry namespace is OttoFlow (not Otto) because
// OttoDIYLib already defines a class named Otto - see DESIGN.md.
//================================================================
#pragma once
#include "OttoConfig.h"

namespace OttoFlow {
  /** Start the robot with the classic biped kit defaults. */
  void start();

  /** Start with a known kit @p preset (standard wiring assumed). */
  void start(Preset preset);

  /** Start with a full custom @p config. */
  void start(const OttoConfig& config);

  /** @return true once start() has run. */
  bool isStarted();

  /** @return the framework version string, e.g. "0.1.0". */
  const char* version();
}
