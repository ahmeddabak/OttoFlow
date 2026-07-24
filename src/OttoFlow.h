//================================================================
// OttoFlow - the one include a sketch needs.
//
//   #include <OttoFlow.h>
//
//   void setup() {
//     OttoFlow::start();          // classic Otto biped kit
//     Face::show(Icon::Heart);
//   }
//
//   void loop() {
//     if (Eyes::closerThanCm(15)) Face::show(Icon::Surprised);
//     else                        Face::show(Icon::Happy);
//   }
//
// Layers (see DESIGN.md):
//   Facades  - Face, Eyes, Voice, Legs, Arms, Gestures (sugar)
//   Modules  - Matrix, Ultrasonic, Buzzer, LegServos, ArmServos (full control)
//   Driver   - OttoDIYLib, reachable via #include <OttoFlowDriver.h>
//================================================================
#pragma once

#include "core/OttoCore.h"
#include "core/OttoConfig.h"
#include "core/Icons.h"
#include "core/Sounds.h"
#include "core/Gestures.h"

// Modules - hardware-truth API (level 2)
#include "modules/Matrix.h"
#include "modules/Ultrasonic.h"
#include "modules/Buzzer.h"
#include "modules/Melody.h"
#include "modules/LegServos.h"
#include "modules/ArmServos.h"
#include "modules/TouchSensor.h"
#include "modules/SoundSensor.h"
#include "modules/LightSensor.h"
#include "modules/Bluetooth.h"
#include "modules/Mpu6050.h"
#include "modules/AppLink.h"

// Facades - expressive API (level 1)
#include "facades/Face.h"
#include "facades/Eyes.h"
#include "facades/Voice.h"
#include "facades/Legs.h"
#include "facades/Arms.h"
#include "facades/Gestures.h"
#include "facades/Motion.h"
#include "facades/Touch.h"
#include "facades/Ears.h"
#include "facades/Balance.h"

// Serial console (costs nothing unless Console::begin() is called)
#include "console/Console.h"
