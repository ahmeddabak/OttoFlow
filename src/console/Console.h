//================================================================
// OttoFlow - console/Console.h
// Interactive serial TEST console: verify each motor and each
// sensor from the Serial Monitor without reflashing. Type `help`
// for the command list.
//
// Deliberately NOT a remote control: no gestures, dances or
// walking here - full control belongs in your program or the
// Otto DIY app (AppLink). The console tests hardware, one part
// at a time.
//
//   void setup() { OttoFlow::start(); Console::begin(9600); }
//   void loop()  { Console::poll(); }
//
// If a sketch never calls Console::begin(), the linker strips the
// console entirely - it costs nothing unless used.
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
