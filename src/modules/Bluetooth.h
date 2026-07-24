//================================================================
// OttoFlow - modules/Bluetooth.h
// Serial Bluetooth module (HC-05/06 or BLE-serial) on two pins
// via SoftwareSerial. Enable in config before use:
//
//   OttoConfig cfg;
//   cfg.bluetooth.enabled = true;   // module TXD->pin 11, RXD->pin 12
//   OttoFlow::start(cfg);
//
// The stream can drive the serial Console or the official Otto
// app protocol (AppLink):
//
//   Console::begin(Bluetooth::stream());   // console over Bluetooth
//   AppLink::begin();                      // Otto DIY app control
//================================================================
#pragma once
#include <Arduino.h>

namespace Bluetooth {
  // Called by OttoFlow::start() when enabled; safe to call again.
  bool begin();
  bool isReady();

  // The Bluetooth serial stream (valid after begin()).
  Stream& stream();
}
