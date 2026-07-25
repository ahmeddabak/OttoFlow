# OttoFlow -- Roadmap

What's planned, in plain language. No versions, no dates -- just the work ahead.
To drop an item, delete its section; nothing already shipped depends on any of these.

---

## Non-blocking motion engine

Today every movement call blocks: `Legs::walkForward(2)` only returns when the
walk is finished, so the robot is blind and deaf while moving.

Planned: movements that run in the background --

```cpp
Legs::startWalkingForward();
if (Eyes::closerThanCm(15)) Legs::stop();   // react WHILE walking
```

with `Legs::isMoving()` to check state and `OttoFlow::update()` called from
`loop()` to drive the motion step by step. This is the single biggest thing raw
OttoDIYLib cannot do, and the current API names were chosen so this can be added
without breaking any existing sketch.

---

## Event system (react automatically)

Instead of checking the sensor yourself every loop, register what should happen
and let the framework watch for it:

```cpp
Events::onObstacleCloserThanCm(15, onObstacle);   // runs when triggered
Events::everyMs(500, blinkMouth);                  // runs on a timer
```

Removes hand-written if/else state machines from reactive sketches.
Depends on the non-blocking engine (events must be able to fire mid-movement),
so it comes after it.

---

## Bench mode in one call

`OttoFlow::benchMode()` -- shorthand for the desk-testing setup used while
developing: all servos detached (`Motion::disable()`), sounds muted
(`Voice::mute()`), serial console started. Today that's three calls; this makes
it one, plus a clear indicator on the matrix that the robot is in test mode.

---

## Custom icons and animations

The matrix currently offers the 31 built-in OttoDIYLib mouth shapes plus single-pixel
drawing. Planned: define your own 8x8 icons and multi-frame animations in a
readable way and show them like built-ins:

```cpp
OTTOFLOW_ICON(MyAlien,
  0b00111100,
  0b01111110,
  ...);
Mouth::showCustom(MyAlien);
```

Stored in flash (PROGMEM), so they cost no RAM.

---

## Arm servo trims

Leg servos have trims; arm servos have none. The arms run on the plain `Servo`
library, so a horn seated a few degrees off means one arm rests visibly lower
than the other, and the only fixes today are reseating the horn or offsetting
every angle by hand in the sketch.

Planned: the same treatment the legs already get --

```cpp
cfg.arms.leftTrim  = 0;
cfg.arms.rightTrim = 5;    // applied to every arm move
```

applied inside `ArmServos::positionLeftDegrees()` / `positionRightDegrees()` so
that `center()`, `up()`, `down()` and the waves all inherit it, plus an `armtrim`
console command for the same adjust-and-look loop as `trim`. Whether they share
the legs' EEPROM block or get their own is the open question.

---

## Servo calibration wizard

Every physical Otto needs small trim corrections so it stands straight.
The API for trims exists (`Legs::setTrimsDegrees()` + `saveTrimsToEeprom()`),
and the console can set all four at once --

```
> trim -4 3 0 -2      (left leg, right leg, left foot, right foot)
> trim save           (stored in EEPROM, loaded on every start)
```

-- but you still tune four numbers at a time, holding in your head which one is
which. Planned: one servo at a time, with guided prompts --

```
> trim wizard
left leg: +/- to adjust, enter to accept
```

Should cover the arms too, once they have trims of their own.

---

## Example sketches

A numbered `examples/` folder, beginner -> advanced:

1. **HelloHeart** -- start the robot, show a heart (the smallest sketch)
2. **ObstacleAvoidance** -- roam and react to obstacles
3. **SerialConsole** -- bench-test hardware from the Serial Monitor
4. **HumanoidArms** -- the arms preset and arm moves
5. **PowerUser** -- custom config, module layer, raw-driver escape hatch

The [wiki's Examples page](https://github.com/ahmeddabak/OttoFlow/wiki/Examples)
already carries sketches of this kind, ready to paste. What is left is bundling
them into the library so the Arduino IDE and PlatformIO list them in their example
browsers -- worth doing once the feature set settles, so they never go stale.

---

## Publish to library registries

Submit to the PlatformIO Registry and the Arduino Library Manager so anyone can
install OttoFlow by name (`lib_deps = OttoFlow` / IDE library search) instead of
a git URL. Best done after the API has survived real users without breaking
changes.

---

## ESP32 / ESP8266 support

Support the WiFi-capable Otto variants. OttoDIYLib already compiles for ESP32;
OttoFlow needs conditional servo/tone backends and a test robot on that board.
Opens the door to web-based remote control later.

---

## More add-on modules

Most kit extras are already shipped (touch, sound sensor, photoresistor,
Bluetooth + official app protocol, MPU-6050). Still open, each following the
extension guide in DESIGN.md (a good way to contribute!):

- **RGB LEDs** -- mood colors
- **APDS-9960** -- hand-gesture / color / proximity sensor found in some kits
- **Tilt-reactive behaviors** -- use the MPU-6050 to detect falls and get up,
  or protest when picked up (sensor module exists; the behaviors don't yet)
