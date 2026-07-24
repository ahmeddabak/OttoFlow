//================================================================
// OttoFlow - console/Console.h
// Interactive serial console: test the robot from the Serial
// Monitor without reflashing. Type `help` for the command list.
//
//   void setup() { OttoFlow::start(); Console::begin(9600); }
//   void loop()  { Console::poll(); }
//
// If a sketch never calls Console::begin(), the linker strips the
// console entirely - it costs nothing unless used.
//
// Flash note (ATmega328): the `gesture` command links all 13
// OttoDIYLib gestures (~6 KB) and is therefore opt-in. Add
//   build_flags = -DOTTOFLOW_CONSOLE_GESTURES
// to enable it; without the flag the console ships without it.
//================================================================
#pragma once
#include <Arduino.h>

namespace Console {
  void begin(unsigned long baud = 9600);   // over USB Serial
  void begin(Stream& stream);              // over any stream, e.g.
                                           // Console::begin(Bluetooth::stream())

  // Call every loop() iteration; handles one pending command.
  void poll();
}
