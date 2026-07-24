#include "OttoCore.h"
#include "Internal.h"
#include "../modules/ArmServos.h"
#include <Otto.h>

static ::Otto     s_driver;   // the one OttoDIYLib instance
static OttoConfig s_config;
static bool       s_started = false;

namespace ottoflow_internal {
  ::Otto&     drv()    { return s_driver; }
  OttoConfig& config() { return s_config; }
}

namespace OttoFlow {

void start()              { start(OttoConfig()); }
void start(Preset preset) { start(OttoConfig(preset)); }

void start(const OttoConfig& config) {
  s_config = config;

  // Leg/foot servos + buzzer
  s_driver.init(s_config.legs.legLeft,  s_config.legs.legRight,
                s_config.legs.footLeft, s_config.legs.footRight,
                s_config.loadTrimsFromEeprom, s_config.buzzer.pin);

  // LED matrix
  s_driver.initMATRIX(s_config.matrix.din, s_config.matrix.cs,
                      s_config.matrix.clk, s_config.matrix.orientation);
  s_driver.matrixIntensity(s_config.matrix.brightness);

  // Ultrasonic "eyes"
  pinMode(s_config.ultrasonic.triggerPin, OUTPUT);
  pinMode(s_config.ultrasonic.echoPin, INPUT);

  // Arm servos (only if this build has them enabled)
  if (s_config.arms.enabled) {
    ArmServos::attach();
  }

  s_started = true;

  if (s_config.buzzer.helloOnStart && !s_config.buzzer.muted) {
    s_driver.sing(S_connection);
  }
}

bool isStarted() { return s_started; }

const char* version() { return "0.1.0"; }

// Escape hatch, declared in <OttoFlowDriver.h> (opt-in include).
::Otto& driver() { return s_driver; }

}  // namespace OttoFlow
