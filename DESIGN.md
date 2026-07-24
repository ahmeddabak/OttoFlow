# OttoFlow — Design Document

The decisions that shape this framework, and why. Contributors: follow these;
propose changes via issues before breaking them.

## Goals

1. **Rapid development** — a working robot behavior in a handful of readable lines.
2. **Layered audience** — beginners never *need* to leave the top layer; power users
   never hit a locked door.
3. **A clear, consistent API** — every identifier states what it does and in which unit.

## Architecture: three layers

```
┌─ Facades   Face, Eyes, Voice, Legs, Arms, Gestures     (src/facades/)
│            Expressive sugar. Inline, zero overhead.
├─ Modules   Matrix, Ultrasonic, Buzzer, LegServos, ArmServos (src/modules/)
│            Hardware-truth names. All real logic lives here.
└─ Driver    OttoDIYLib                                  (dependency)
             Reached only by module .cpp files — and by users
             via the official escape hatch, OttoFlowDriver.h.
```

Rules:
- Each layer only talks to the layer directly below it.
- Facades contain **no logic** — only inline forwarding. This keeps the two
  vocabularies (friendly + technical) in lockstep with zero duplication.
- Public headers (`OttoFlow.h` and everything it includes) never include
  OttoDIYLib headers. This keeps its lowercase macros (`heart`, `smile`, …)
  out of user sketches. Modules include `<Otto.h>` in their `.cpp` only.

## The vocabulary problem

What one person calls a *face*, another calls a *mouth* or a *display*. Popular
frameworks solve this by layering: unambiguous technical names underneath
(nobody argues what `Matrix` means), expressive names on top as documented
sugar (`Face`). Both are official; the technical layer is the truth.

## Naming rules

- **Units live in the name**: `distanceCm()`, `playToneHz()`, `periodMs`,
  `positionLeftDegrees()`. Never a bare number with an implicit unit.
- **Directions are words, not signs**: `walkForward(2)` / `walkBackward(2)`,
  never `walk(2, 1000, -1)` in user-facing code.
- **Conditions read as sentences**: `Eyes::closerThanCm(15)`.
- **Enums over magic numbers**: `Icon::Heart`, `Sound::Happy`, `Gesture::Victory`.
- PascalCase namespaces & enum values, camelCase functions.
- **Plain hardware names over domain jargon**: the leg module is `LegServos`
  (symmetric with `ArmServos`), not `Gait` — a beginner should never need a
  robotics glossary to guess what a module controls. Clarity beats the
  technically fancier term.

## Why `OttoFlow::start()` and not `Otto::start()`

OttoDIYLib defines a C++ **class named `Otto`**. A namespace with the same name
cannot coexist with it in a translation unit — and the escape hatch requires
both to be visible at once. Hence the entry point is `OttoFlow::` (on-brand
anyway), and the driver class keeps its original name.

## Configuration: zero-config → preset → override

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
- `Motion::disable()` detaches **all** servos — legs *and* arms — so "the robot
  must not move" is one call, never a per-module checklist. `Legs::disable()` /
  `Arms::relax()` switch off a single group. Disabled movement calls are silent
  no-ops — sketches don't need `#ifdef`s.
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

1. Create `src/modules/YourPart.h/.cpp` — a namespace with clearly-named,
   unit-explicit functions. Reach the shared driver/config through
   `core/Internal.h` if needed.
2. If a friendlier vocabulary helps, add an inline facade in `src/facades/`.
3. Add config (pins, enable flag) to `OttoConfig` with kit-accurate defaults,
   and wire initialization into `OttoFlow::start()`.
4. Ship an example sketch under `examples/` (folder planned — see ROADMAP.md).

A module that follows the naming rules and the guard pattern
(disabled ⇒ silent no-op) will feel native next to the built-ins.

## Hardware scope (v1)

Arduino Nano (ATmega328), classic Otto biped kit: 4 leg/foot servos, HC-SR04,
MAX7219 8x8 matrix, buzzer — plus optional 2 arm servos (Humanoid build,
config-enabled). Wider hardware is roadmap territory.

## License

GPL-3.0, required by wrapping OttoDIYLib (GPL-3.0). All contributions are
accepted under the same license.
