//================================================================
// OttoFlow - modules/AppLink.h
// Control Otto from the official Otto DIY phone app. Implements
// the app's serial command protocol (compatible with the
// Otto_APP example firmware), usually over Bluetooth:
//
//   OttoConfig cfg;
//   cfg.bluetooth.enabled = true;
//   OttoFlow::start(cfg);
//
//   void setup2() { AppLink::begin(); }     // uses Bluetooth
//   void loop()  { AppLink::poll(); }       // call every iteration
//
// Protocol commands: S (stop), M (movement), H (gesture),
// K (sound), L (matrix pattern), T (tone), C (save trims),
// G (direct servo positions). Acknowledged with &&A%% / &&F%%.
//
// Movements respect Legs::disable() - a disabled robot answers
// the app but does not move.
//================================================================
#pragma once
#include <Arduino.h>

namespace AppLink {
  /** Start listening for app commands on the Bluetooth stream. */
  void begin();
  /** Start listening for app commands on any @p stream (e.g. Serial). */
  void begin(Stream& stream);

  /** Handle incoming commands and keep the current movement running. Call every loop() iteration. */
  void poll();
}
