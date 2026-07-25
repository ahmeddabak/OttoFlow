/**
 * @file OttoFlowDriver.h
 * @brief The official escape hatch - reach the raw OttoDIYLib driver.
 *
 * OttoFlow hides nothing. Include this header to reach the raw
 * OttoDIYLib driver instance underneath the framework:
 *
 * @code
 *   #include <OttoFlow.h>
 *   #include <OttoFlowDriver.h>
 *
 *   Otto& raw = OttoFlow::driver();
 *   raw.oscillateServos(...);      // anything OttoDIYLib can do
 * @endcode
 *
 * This is a separate opt-in include (not part of <OttoFlow.h>)
 * because it pulls in all of OttoDIYLib's headers, including its
 * lowercase mouth macros (heart, smile, ...) which would pollute
 * beginner sketches.
 */
#pragma once
#include <Otto.h>

namespace OttoFlow {
  /**
   * @return the OttoDIYLib instance the framework drives (valid after
   * OttoFlow::start()). Changes made here are visible to the framework
   * and vice versa.
   */
  ::Otto& driver();
}
