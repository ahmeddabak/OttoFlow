# OttoFlow -- Design Document

The decisions that shape this framework, and why. Contributors: follow these;
propose changes via issues before breaking them.

## Goals

1. **Rapid development** -- a working robot behavior in a handful of readable lines.
2. **Layered audience** -- beginners never *need* to leave the top layer; power users
   never hit a locked door.
3. **A clear, consistent API** -- every identifier states what it does and in which unit.

## Architecture: three layers

```
+- Facades   Mouth, Eyes, Voice, Legs, Arms, Gestures,    (src/facades/)
|            Motion, Touch, Ears, Balance
|            Expressive sugar. Inline, zero overhead.
+- Modules   Matrix, Ultrasonic, Buzzer, Melody,         (src/modules/)
|            LegServos, ArmServos, TouchSensor,
|            SoundSensor, LightSensor, Bluetooth,
|            Mpu6050, AppLink
|            Hardware-truth names. All real logic lives here.
+- Driver    OttoDIYLib                                  (dependency)
             Reached only by module .cpp files -- and by users
             via the official escape hatch, OttoFlowDriver.h.
```

Rules:
- Each layer only talks to the layer directly below it.
- Facades contain **no logic** -- only inline forwarding. This keeps the two
  vocabularies (friendly + technical) in lockstep with zero duplication.
- Public headers (`OttoFlow.h` and everything it includes) never include
  OttoDIYLib headers. This keeps its lowercase macros (`heart`, `smile`, ...)
  out of user sketches. Modules include `<Otto.h>` in their `.cpp` only.

## The vocabulary problem

What one person calls a *face*, another calls a *mouth* or a *display*. Popular
frameworks solve this by layering: unambiguous technical names underneath
(nobody argues what `Matrix` means), expressive names on top as documented
sugar (`Mouth`). Both are official; the technical layer is the truth.

For the sugar word itself, OttoFlow deliberately adopts the upstream
OttoDIYLib/community vocabulary -- the matrix is Otto's **mouth** (`putMouth`
in the driver, "mouth" in every Otto tutorial). Ecosystem consistency beats
inventing a prettier word.

## Naming rules

- **Units live in the name**: `distanceCm()`, `playToneHz()`, `periodMs`,
  `positionLeftDegrees()`. Never a bare number with an implicit unit.
- **Directions are words, not signs**: `walkForward(2)` / `walkBackward(2)`,
  never `walk(2, 1000, -1)` in user-facing code.
- **Conditions read as sentences**: `Eyes::closerThanCm(15)`.
- **Enums over magic numbers**: `Icon::Heart`, `Sound::Happy`, `Gesture::Victory`.
- PascalCase namespaces & enum values, camelCase functions.
- **Plain hardware names over domain jargon**: the leg module is `LegServos`
  (symmetric with `ArmServos`), not `Gait` -- a beginner should never need a
  robotics glossary to guess what a module controls. Clarity beats the
  technically fancier term.
- **Siblings stay symmetric**: if `Legs` has `center()`, `Arms` has `center()`,
  and both mean the same thing. Learning one facade should let you guess the next.
- **Poses are named for the pose**: `center()` says where the servos end up.
  `home()` is kept as a documented alias of it, because both words are equally
  natural for the same stance. An alias is only ever a **synonym** -- never two
  names whose behaviour differs.

## Left and right are mirrored, not identical

The two arm servos are mounted facing opposite ways, so the same physical pose
needs opposite angles. Every **both-arm** call therefore takes the *left* servo's
angle and writes `180 - angle` to the right: `Arms::up()` is left 180 / right 0,
`raiseBoth(120)` is left 120 / right 60. `waveRight()` is mirrored against
`waveLeft()` the same way, so the two greetings look identical on the robot.

**Single-servo** calls -- `Arms::raiseLeft()`, `ArmServos::positionRightDegrees()`,
the console's `arm l|r <angle>` -- stay raw, because calibration and bench testing
have to address one servo in its own terms. The rule: *a call that names one servo
speaks that servo's angles; a call that names both speaks in poses.*

The mirroring lives in `ArmServos::positionBothMirroredDegrees()`, not in the
`Arms` facade -- facades hold no logic. Legs need no equivalent: every leg pose
call names all four servos explicitly (`positionAllDegrees(ll, lr, fl, fr)`), so
there is no both-at-once call whose meaning could be ambiguous.

## Why `OttoFlow::start()` and not `Otto::start()`

OttoDIYLib defines a C++ **class named `Otto`**. A namespace with the same name
cannot coexist with it in a translation unit -- and the escape hatch requires
both to be visible at once. Hence the entry point is `OttoFlow::` (on-brand
anyway), and the driver class keeps its original name.

## Configuration: zero-config -> preset -> override

```cpp
OttoFlow::start();                   // level 0: standard kit, nothing to learn
OttoFlow::start(Preset::Humanoid);   // level 1: known build, standard wiring
OttoConfig cfg = Preset::Humanoid;   // level 2: change any pin/setting
cfg.arms.leftPin = 10;
OttoFlow::start(cfg);
```

Defaults must always match the official kit wiring, so the zero-config path
works for the largest group of users unmodified.

## Safety & bench-testing philosophy

Hardware development happens one feature at a time. The framework supports
that as a first-class workflow:
- `Motion::disable()` detaches **all** servos -- legs *and* arms -- so "the robot
  must not move" is one call, never a per-module checklist. `Legs::disable()` /
  `Arms::relax()` switch off a single group. Disabled movement calls are silent
  no-ops -- sketches don't need `#ifdef`s.
- `Voice::mute()` silences every sound call the same way.
- The serial console exercises any feature interactively without reflashing.

## Blocking in v1, async-ready by design

All movement calls block (they return when the motion completes) because the
underlying OttoDIYLib is blocking and beginners reason most easily about
sequential code. Names are chosen so the non-blocking engine (ROADMAP) can add
`startWalking()` / `isMoving()` / `stop()` alongside without renaming or
breaking anything.

## The escape hatch is official

`OttoFlow::driver()` (via `#include <OttoFlowDriver.h>`) hands out the raw
OttoDIYLib instance. It is documented, supported, and deliberate: a framework
that hides the lower layer loses its advanced users. It lives in a separate
opt-in header only to keep macro pollution out of beginner sketches.

## Extending OttoFlow (custom modules)

Add a new capability as a module + optional facade:

1. Create `src/modules/YourPart.h/.cpp` -- a namespace with clearly-named,
   unit-explicit functions. Reach the shared driver/config through
   `core/Internal.h` if needed.
2. If a friendlier vocabulary helps, add an inline facade in `src/facades/`.
3. Add config (pins, enable flag) to `OttoConfig` with kit-accurate defaults,
   and wire initialization into `OttoFlow::start()`.
4. Ship an example sketch under `examples/` (folder planned -- see ROADMAP.md).
5. Document it in the wiki -- see below.

A module that follows the naming rules and the guard pattern
(disabled => silent no-op) will feel native next to the built-ins.

## Documentation is part of the API

The [wiki](https://github.com/ahmeddabak/OttoFlow/wiki) is the manual, and it is
written with the code rather than after it. The standard:

- Every facade has a **page of its own**, named after the part of the robot it
  drives -- grouping several parts onto one page hides them. Modules get a section
  each in the `Modules` reference page, except where a module has no facade
  (`LightSensor` -> the `Light` page), which then gets the page instead.
- Every public function appears in **`API-Reference`**. A new page is also added
  to **`_Sidebar`** and **`Home`**.
- A public API change -- new function, rename, changed behaviour, new console
  command -- is not finished until the matching wiki change lands with it.

The wiki is a separate git repository (the GitHub wiki of this project), so this
is two commits, not one. A feature nobody can find is not a feature.

## Hardware scope

Arduino Nano (ATmega328), Otto biped/Humanoid kits: 4 leg/foot servos, HC-SR04,
MAX7219 8x8 matrix, buzzer -- plus the optional kit hardware, each config-enabled
or passively available: 2 arm servos, touch sensor, sound sensor (microphone),
photoresistor, Bluetooth serial module (incl. the official app protocol), and
the MPU-6050 6-axis motion sensor. Other boards (ESP32) are roadmap territory.

## License

GPL-3.0, required by wrapping OttoDIYLib (GPL-3.0). All contributions are
accepted under the same license.
