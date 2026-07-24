# OttoFlow

**Rapid development framework for [Otto DIY](https://www.ottodiy.com/) robots.**
Expressive facades over hardware-truth modules, zero-config kit presets, and full
low-level access â€” nothing hidden.

```cpp
#include <OttoFlow.h>

void setup() {
  OttoFlow::start();               // classic Otto kit: zero config
  Mouth::show(Icon::Heart);
}

void loop() {
  if (Eyes::closerThanCm(15)) {
    Mouth::show(Icon::Surprised);
    Legs::walkBackward(2);
  } else {
    Mouth::show(Icon::Happy);
    Legs::walkForward(1);
  }
}
```

That's a complete obstacle-avoiding robot. No pin maps, no libraries to wire up, no magic numbers.

## Why OttoFlow?

| Task | Raw OttoDIYLib | OttoFlow |
|---|---|---|
| First sketch | pin defines + init boilerplate | `OttoFlow::start();` |
| Show a heart | `putMouth(13)` or `putMouth(heart)` | `Mouth::show(Icon::Heart)` |
| Read distance | write your own `pulseIn` code | `Eyes::distanceCm()` (median-filtered) |
| Walk | `walk(2, 1000, 1)` â€” what's 1? | `Legs::walkForward(2)` |
| Test hardware safely | comment out code, reflash | `Motion::disable()` + serial console |
| Advanced access | â€” | full module layer + `OttoFlow::driver()` |

## The three layers

```
Facades   Mouth::show(Icon::Heart)          â† expressive, beginner-friendly
Modules   Matrix::drawPixel(3, 4, true)    â† hardware-truth names, full control
Driver    OttoFlow::driver().oscillateServos(...)   â† raw OttoDIYLib, official escape hatch
```

Start at the top. Drop down whenever you need more. **No locked doors.**

## Quick start (PlatformIO)

```ini
[env:nanoatmega328]
platform = atmelavr
board = nanoatmega328
framework = arduino
lib_deps = https://github.com/ahmeddabak/OttoFlow.git
```

```cpp
#include <OttoFlow.h>
void setup() { OttoFlow::start(); Mouth::show(Icon::Heart); }
void loop()  {}
```

## Presets & configuration

```cpp
OttoFlow::start();                     // classic biped kit (default wiring)
OttoFlow::start(Preset::Humanoid);     // biped + arms on pins 6/7

OttoConfig cfg = Preset::Humanoid;     // power user: override anything
cfg.arms.leftPin = 10;
cfg.matrix.brightness = 8;
cfg.ultrasonic.samples = 5;
OttoFlow::start(cfg);
```

Default wiring (classic kit): legs 2/3, feet 4/5, buzzer 13, ultrasonic 8/9, matrix DIN A3 / CS A2 / CLK A1.

## Serial console

Test every part of the robot from the Serial Monitor â€” no reflashing:

```cpp
void setup() { OttoFlow::start(); Console::begin(9600); }
void loop()  { Console::poll(); }
```

```
> dist
23 cm
> mouth heart
> walk 2 f
> legs off
```

## Bench testing

Building feature by feature? Keep the robot still and silent while you verify sensors:

```cpp
Motion::disable();  // ALL servos detached (legs + arms): no movement, no jitter
Voice::mute();      // no sounds
```

(`Legs::disable()` / `Arms::relax()` switch off just one servo group.)

## API tour

- **`Mouth`** â€” `show(Icon::â€¦)`, `showDigit(7)`, `scrollText("HI")`, `setBrightness(8)`, `clear()`
- **`Eyes`** â€” `distanceCm()`, `closerThanCm(15)`, `fartherThanCm(50)`
- **`Voice`** â€” `play(Sound::Happy)`, `playToneHz(440, 200)`, `playHappyBirthday()`, `mute()` / `unmute()`
- **`Legs`** â€” `walkForward(2)`, `turnLeft(3)`, `moonwalkLeft()`, `home()`, `enable()` / `disable()`, trims
- **`Motion`** â€” `disable()` / `enable()` â€” ALL servos (legs + arms) in one call
- **`Arms`** â€” `raiseBoth()`, `waveRight()`, `relax()` *(humanoid builds)*
- **`Gestures`** â€” `play(Gesture::Victory)` â€” movement + mouth + sound in one call
- **`Touch`** â€” `isTouched()`, `wasTapped()` (debounced, works with toggle-mode sensors)
- **`Ears`** â€” `loudnessPercent()`, `hearsSoundLouderThanPercent(60)` *(microphone)*
- **`Balance`** â€” `pitchDegrees()`, `isUpsideDown()`, `isShakenHarderThanG(0.6)` *(MPU-6050)*
- **`AppLink`** â€” control Otto from the official Otto DIY phone app over Bluetooth
- **Modules** â€” `Matrix`, `Ultrasonic`, `Buzzer`, `Melody`, `LegServos`, `ArmServos`,
  `TouchSensor`, `SoundSensor`, `LightSensor`, `Bluetooth`, `Mpu6050` for full control
- **Driver** â€” `#include <OttoFlowDriver.h>` â†’ `OttoFlow::driver()` is the raw OttoDIYLib object

Every name states its meaning and unit: `distanceCm()`, not `dist()`; `walkForward(2)`, not `walk(2,1000,1)`.

## Examples

Coming once the feature set settles â€” see [ROADMAP.md](ROADMAP.md).

## Project documents

- [DESIGN.md](DESIGN.md) â€” architecture and the reasoning behind every API decision
- [ROADMAP.md](ROADMAP.md) â€” what's planned next (non-blocking engine, events, â€¦)

## License

GPL-3.0 â€” required and proudly inherited from [OttoDIYLib](https://github.com/OttoDIY/OttoDIYLib),
which OttoFlow wraps as its driver layer. Support Otto DIY by purchasing kits at
[ottodiy.com](https://www.ottodiy.com/).
