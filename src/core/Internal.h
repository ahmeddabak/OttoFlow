//================================================================
// OttoFlow - core/Internal.h
// Framework-internal plumbing shared by the modules. Not part of
// the public API - user sketches never include this. Modules use
// it to reach the OttoDIYLib driver instance and the active config.
//================================================================
#pragma once
#include "OttoConfig.h"

class Otto;  // OttoDIYLib driver class (defined in <Otto.h>, included by .cpp files only)

namespace ottoflow_internal {
  /** @return the one shared OttoDIYLib driver instance. */
  ::Otto&     drv();
  /** @return the active configuration passed to OttoFlow::start(). */
  OttoConfig& config();
}
