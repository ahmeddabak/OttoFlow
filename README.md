# OttoFlow

**Rapid development framework for [Otto DIY](https://www.ottodiy.com/) robots.**
Expressive facades over hardware-truth modules, zero-config kit presets, and full
low-level access -- nothing hidden.

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
| Walk | `walk(2, 1000, 1)` -- what's 1? | `Legs::walkForward(2)` |
| Test hardware safely | comment out code, reflash | `Motion::disable()` + serial console |
| Advanced access | -- | full module layer + `OttoFlow::driver()` |

## The three layers

```
Facades   Mouth::show(Icon::Heart)          <- expressive, beginner-friendly
Modules   Matrix::drawPixel(3, 4, true)    <- hardware-truth names, full control
Driver    OttoFlow::driver().oscillateServos(...)   <- raw OttoDIYLib, official escape hatch
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

Test every part of the robot from the Serial Monitor -- no reflashing:

```cpp
void setup() { OttoFlow::start(); Console::begin(9600); }
void loop()  { Console::poll(); }
```

```
> dist
23 cm
> mouth heart
> legs on
> center
> arms up
> watch mic
```

`help` lists every command.

## Bench testing

Building feature by feature? Keep the robot still and silent while you verify sensors:

```cpp
Motion::disable();  // ALL servos detached (legs + arms): no movement, no jitter
Voice::mute();      // no sounds
```

(`Legs::disable()` / `Arms::relax()` switch off just one servo group.)

## API tour

- **`Mouth`** -- `show(Icon::...)`, `showDigit(7)`, `scrollText("HI")`, `setBrightness(8)`, `clear()`
- **`Eyes`** -- `distanceCm()`, `closerThanCm(15)`, `fartherThanCm(50)`
- **`Voice`** -- `play(Sound::Happy)`, `playToneHz(440, 200)`, `playHappyBirthday()`, `mute()` / `unmute()`
- **`Legs`** -- `walkForward(2)`, `turnLeft(3)`, `moonwalkLeft()`, `center()`, `enable()` / `disable()`, trims
- **`Motion`** -- `disable()` / `enable()` -- ALL servos (legs + arms) in one call
- **`Arms`** -- `center()`, `up()`, `down()`, `raiseBoth()`, `waveRight()`, `relax()` *(humanoid builds)*
- **`Gestures`** -- `play(Gesture::Victory)` -- movement + mouth + sound in one call
- **`Touch`** -- `isTouched()`, `wasTapped()` (debounced, works with toggle-mode sensors)
- **`Ears`** -- `loudnessPercent()`, `hearsSoundLouderThanPercent(60)` *(microphone)*
- **`LightSensor`** -- `brightnessPercent()`, `isDarkerThanPercent(20)` *(photoresistor)*
- **`Balance`** -- `pitchDegrees()`, `isUpsideDown()`, `isShakenHarderThanG(0.6)` *(MPU-6050)*
- **`AppLink`** -- control Otto from the official Otto DIY phone app over Bluetooth
- **Modules** -- `Matrix`, `Ultrasonic`, `Buzzer`, `Melody`, `LegServos`, `ArmServos`,
  `TouchSensor`, `SoundSensor`, `LightSensor`, `Bluetooth`, `Mpu6050` for full control
- **Driver** -- `#include <OttoFlowDriver.h>` -> `OttoFlow::driver()` is the raw OttoDIYLib object

Every name states its meaning and unit: `distanceCm()`, not `dist()`; `walkForward(2)`, not `walk(2,1000,1)`.

`home()` is an alias for `center()` on both `Legs` and `Arms`. Both-arm calls mirror the
right servo (`up()` is left 180 / right 0), because the two arm servos face opposite ways.

## Documentation

The **[wiki](https://github.com/ahmeddabak/OttoFlow/wiki)** is the full manual -- a page per
part of the robot, plus configuration, calibration, and troubleshooting:

- [Installation](https://github.com/ahmeddabak/OttoFlow/wiki/Installation) and [Configuration](https://github.com/ahmeddabak/OttoFlow/wiki/Configuration) -- presets, pins, every setting
- [Examples](https://github.com/ahmeddabak/OttoFlow/wiki/Examples) -- complete, ready-to-flash sketches
- [Mouth](https://github.com/ahmeddabak/OttoFlow/wiki/Mouth), [Voice](https://github.com/ahmeddabak/OttoFlow/wiki/Voice), [Movement](https://github.com/ahmeddabak/OttoFlow/wiki/Movement), [Arms](https://github.com/ahmeddabak/OttoFlow/wiki/Arms), [Gestures](https://github.com/ahmeddabak/OttoFlow/wiki/Gestures), [Motion](https://github.com/ahmeddabak/OttoFlow/wiki/Motion)
- [Eyes](https://github.com/ahmeddabak/OttoFlow/wiki/Eyes), [Ears](https://github.com/ahmeddabak/OttoFlow/wiki/Ears), [Touch](https://github.com/ahmeddabak/OttoFlow/wiki/Touch), [Light](https://github.com/ahmeddabak/OttoFlow/wiki/Light), [Balance](https://github.com/ahmeddabak/OttoFlow/wiki/Balance)
- [Bench Testing](https://github.com/ahmeddabak/OttoFlow/wiki/Bench-Testing), [Serial Console](https://github.com/ahmeddabak/OttoFlow/wiki/Serial-Console), [Calibration](https://github.com/ahmeddabak/OttoFlow/wiki/Calibration)
- [API Reference](https://github.com/ahmeddabak/OttoFlow/wiki/API-Reference) -- every public function on one page

Bundled `examples/` sketches are on the [ROADMAP](ROADMAP.md); until then the wiki's
Examples page has the same sketches, ready to paste.

## Project documents

- [DESIGN.md](DESIGN.md) -- architecture and the reasoning behind every API decision
- [ROADMAP.md](ROADMAP.md) -- what's planned next (non-blocking engine, events, ...)

## License

GPL-3.0 -- required and proudly inherited from [OttoDIYLib](https://github.com/OttoDIY/OttoDIYLib),
which OttoFlow wraps as its driver layer. Support Otto DIY by purchasing kits at
[ottodiy.com](https://www.ottodiy.com/).
