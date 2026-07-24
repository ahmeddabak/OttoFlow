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
  void begin();                 // listen on the Bluetooth stream
  void begin(Stream& stream);   // listen on any stream (e.g. Serial)

  // Call every loop() iteration: handles incoming commands and
  // keeps the current movement running.
  void poll();
}
