#include "Bluetooth.h"
#include "../core/Internal.h"
#include <SoftwareSerial.h>

using ottoflow_internal::config;

namespace Bluetooth {

// Constructed on first begin() so the pins come from the config.
static SoftwareSerial* s_port  = nullptr;
static bool            s_ready = false;

bool begin() {
  if (!config().bluetooth.enabled) return false;
  if (s_port == nullptr) {
    s_port = new SoftwareSerial(config().bluetooth.rxPin,
                                config().bluetooth.txPin);
  }
  s_port->begin(config().bluetooth.baud);
  s_ready = true;
  return true;
}

bool isReady() { return s_ready; }

Stream& stream() {
  static SoftwareSerial fallback(255, 255);   // inert stream if begin() was skipped
  return s_ready ? (Stream&)*s_port : (Stream&)fallback;
}

}  // namespace Bluetooth
