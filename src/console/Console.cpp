#include "Console.h"
#include "../core/OttoCore.h"
#include "../facades/Face.h"
#include "../facades/Eyes.h"
#include "../facades/Voice.h"
#include "../facades/Legs.h"
#include "../facades/Arms.h"
#include "../facades/Motion.h"
#include "../facades/Touch.h"
#include "../facades/Ears.h"
#include "../facades/Balance.h"
#include "../facades/Gestures.h"
#include "../modules/LightSensor.h"

#include <string.h>

namespace Console {

static Stream* s_stream = nullptr;
static char    s_line[40];
static uint8_t s_length = 0;

static void printBanner() {
  s_stream->print(F("OttoFlow "));
  s_stream->print(OttoFlow::version());
  s_stream->println(F(" console - type 'help'"));
}

void begin(unsigned long baud) {
  Serial.begin(baud);
  s_stream = &Serial;
  printBanner();
}

void begin(Stream& stream) {
  s_stream = &stream;
  printBanner();
}

static void printHelp() {
  s_stream->println(F("Sensors:"));
#ifndef OTTOFLOW_CONSOLE_NO_MPU
  s_stream->println(F("  dist touch light mic tilt accel"));
#else
  s_stream->println(F("  dist touch light mic"));
#endif
  s_stream->println(F("Matrix:"));
  s_stream->println(F("  face <name>   heart happy smile sad angry surprised"));
  s_stream->println(F("                confused tongue ok x question line"));
  s_stream->println(F("  digit <0-9> | text <msg> | bright <0-15> | clear"));
  s_stream->println(F("Sound:"));
  s_stream->println(F("  beep | sing | sound <1-19> | mute | unmute"));
  s_stream->println(F("Servos (enable first!):"));
  s_stream->println(F("  legs on|off | motion on|off | home"));
  s_stream->println(F("  walk <steps> f|b | turn <steps> l|r"));
  s_stream->println(F("  servo ll|lr|fl|fr <0-180>      one servo"));
  s_stream->println(F("  pose <ll> <lr> <fl> <fr> [ms]  all four"));
#ifndef OTTOFLOW_CONSOLE_NO_DANCE
  s_stream->println(F("  dance <name>  updown swing tiptoe jitter ascend"));
  s_stream->println(F("                moonl moonr crusl crusr flapf flapb"));
#endif
  s_stream->println(F("  bend l|r | shake l|r | jump"));
#ifdef OTTOFLOW_CONSOLE_GESTURES
  s_stream->println(F("  gesture <name>  happy superhappy sad sleep fart"));
  s_stream->println(F("                  confused love angry fretful magic"));
  s_stream->println(F("                  wave victory fail"));
#endif
  s_stream->println(F("  arms up|down|off | armwave l|r"));
  s_stream->println(F("  trim <ll> <lr> <fl> <fr> | trim save"));
  s_stream->println(F("  version"));
}

static bool faceByName(const char* name) {
  Icon icon;
  if      (strcmp_P(name, PSTR("heart")) == 0)     icon = Icon::Heart;
  else if (strcmp_P(name, PSTR("happy")) == 0)     icon = Icon::Happy;
  else if (strcmp_P(name, PSTR("smile")) == 0)     icon = Icon::Smile;
  else if (strcmp_P(name, PSTR("sad")) == 0)       icon = Icon::Sad;
  else if (strcmp_P(name, PSTR("angry")) == 0)     icon = Icon::Angry;
  else if (strcmp_P(name, PSTR("surprised")) == 0) icon = Icon::Surprised;
  else if (strcmp_P(name, PSTR("confused")) == 0)  icon = Icon::Confused;
  else if (strcmp_P(name, PSTR("tongue")) == 0)    icon = Icon::TongueOut;
  else if (strcmp_P(name, PSTR("ok")) == 0)        icon = Icon::Ok;
  else if (strcmp_P(name, PSTR("x")) == 0)         icon = Icon::X;
  else if (strcmp_P(name, PSTR("question")) == 0)  icon = Icon::Question;
  else if (strcmp_P(name, PSTR("line")) == 0)      icon = Icon::Line;
  else return false;
  Face::show(icon);
  return true;
}

#ifdef OTTOFLOW_CONSOLE_GESTURES
static bool gestureByName(const char* name) {
  Gesture gesture;
  if      (strcmp_P(name, PSTR("happy")) == 0)      gesture = Gesture::Happy;
  else if (strcmp_P(name, PSTR("superhappy")) == 0) gesture = Gesture::SuperHappy;
  else if (strcmp_P(name, PSTR("sad")) == 0)        gesture = Gesture::Sad;
  else if (strcmp_P(name, PSTR("sleep")) == 0)      gesture = Gesture::Sleeping;
  else if (strcmp_P(name, PSTR("fart")) == 0)       gesture = Gesture::Fart;
  else if (strcmp_P(name, PSTR("confused")) == 0)   gesture = Gesture::Confused;
  else if (strcmp_P(name, PSTR("love")) == 0)       gesture = Gesture::Love;
  else if (strcmp_P(name, PSTR("angry")) == 0)      gesture = Gesture::Angry;
  else if (strcmp_P(name, PSTR("fretful")) == 0)    gesture = Gesture::Fretful;
  else if (strcmp_P(name, PSTR("magic")) == 0)      gesture = Gesture::Magic;
  else if (strcmp_P(name, PSTR("wave")) == 0)       gesture = Gesture::Wave;
  else if (strcmp_P(name, PSTR("victory")) == 0)    gesture = Gesture::Victory;
  else if (strcmp_P(name, PSTR("fail")) == 0)       gesture = Gesture::Fail;
  else return false;
  Gestures::play(gesture);
  return true;
}
#endif

#ifndef OTTOFLOW_CONSOLE_NO_DANCE
static bool danceByName(const char* name) {
  if      (strcmp_P(name, PSTR("updown")) == 0) Legs::upDown();
  else if (strcmp_P(name, PSTR("swing")) == 0)  Legs::swing();
  else if (strcmp_P(name, PSTR("tiptoe")) == 0) Legs::tiptoeSwing();
  else if (strcmp_P(name, PSTR("jitter")) == 0) Legs::jitter();
  else if (strcmp_P(name, PSTR("ascend")) == 0) Legs::ascendingTurn();
  else if (strcmp_P(name, PSTR("moonl")) == 0)  Legs::moonwalkLeft();
  else if (strcmp_P(name, PSTR("moonr")) == 0)  Legs::moonwalkRight();
  else if (strcmp_P(name, PSTR("crusl")) == 0)  Legs::crusaitoLeft();
  else if (strcmp_P(name, PSTR("crusr")) == 0)  Legs::crusaitoRight();
  else if (strcmp_P(name, PSTR("flapf")) == 0)  Legs::flapForward();
  else if (strcmp_P(name, PSTR("flapb")) == 0)  Legs::flapBackward();
  else return false;
  return true;
}
#endif

// Movement commands need the leg servos enabled.
static bool legsReady() {
  if (Legs::isEnabled()) return true;
  s_stream->println(F("legs are off - 'legs on' first"));
  return false;
}

static void handle(char* line) {
  char* command = strtok(line, " ");
  if (command == nullptr) return;

  if (strcmp_P(command, PSTR("help")) == 0) {
    printHelp();

  //-- Sensors ------------------------------------------------------
  } else if (strcmp_P(command, PSTR("dist")) == 0) {
    long cm = Eyes::distanceCm();
    if (cm >= Eyes::OUT_OF_RANGE_CM) s_stream->println(F("out of range"));
    else { s_stream->print(cm); s_stream->println(F(" cm")); }

  } else if (strcmp_P(command, PSTR("touch")) == 0) {
    s_stream->println(Touch::isTouched() ? F("touched") : F("not touched"));

  } else if (strcmp_P(command, PSTR("light")) == 0) {
    s_stream->print(LightSensor::brightnessPercent()); s_stream->println(F(" %"));

  } else if (strcmp_P(command, PSTR("mic")) == 0) {
    s_stream->print(Ears::loudnessPercent()); s_stream->println(F(" %"));

#ifndef OTTOFLOW_CONSOLE_NO_MPU
  } else if (strcmp_P(command, PSTR("tilt")) == 0) {
    if (!Mpu6050::isConnected()) { s_stream->println(F("MPU-6050 not connected/enabled")); return; }
    s_stream->print(F("pitch "));  s_stream->print(Balance::pitchDegrees(), 1);
    s_stream->print(F("  roll ")); s_stream->println(Balance::rollDegrees(), 1);

  } else if (strcmp_P(command, PSTR("accel")) == 0) {
    if (!Mpu6050::isConnected()) { s_stream->println(F("MPU-6050 not connected/enabled")); return; }
    float x, y, z;
    Mpu6050::readAccelerationG(x, y, z);
    s_stream->print(F("x ")); s_stream->print(x, 2);
    s_stream->print(F("  y ")); s_stream->print(y, 2);
    s_stream->print(F("  z ")); s_stream->print(z, 2);
    s_stream->println(F(" g"));
#endif

  //-- Matrix -------------------------------------------------------
  } else if (strcmp_P(command, PSTR("face")) == 0) {
    const char* name = strtok(nullptr, " ");
    if (name == nullptr || !faceByName(name)) s_stream->println(F("unknown face"));

  } else if (strcmp_P(command, PSTR("digit")) == 0) {
    const char* arg = strtok(nullptr, " ");
    if (arg) Face::showDigit(atoi(arg));

  } else if (strcmp_P(command, PSTR("text")) == 0) {
    char* message = strtok(nullptr, "");
    if (message) Face::scrollText(message);

  } else if (strcmp_P(command, PSTR("bright")) == 0) {
    const char* arg = strtok(nullptr, " ");
    if (arg) Face::setBrightness(atoi(arg));

  } else if (strcmp_P(command, PSTR("clear")) == 0) {
    Face::clear();

  //-- Sound --------------------------------------------------------
  } else if (strcmp_P(command, PSTR("beep")) == 0) {
    Voice::play(Sound::Hello);

  } else if (strcmp_P(command, PSTR("sing")) == 0) {
    Voice::playHappyBirthday();

  } else if (strcmp_P(command, PSTR("sound")) == 0) {
    const char* arg = strtok(nullptr, " ");
    int id = arg ? atoi(arg) : 0;
    if (id >= 1 && id <= 19) Voice::play((Sound)(id - 1));
    else s_stream->println(F("sound 1-19"));

  } else if (strcmp_P(command, PSTR("mute")) == 0) {
    Voice::mute();  s_stream->println(F("muted"));

  } else if (strcmp_P(command, PSTR("unmute")) == 0) {
    Voice::unmute();  s_stream->println(F("unmuted"));

  //-- Servo switches -----------------------------------------------
  } else if (strcmp_P(command, PSTR("legs")) == 0) {
    const char* state = strtok(nullptr, " ");
    if (state && strcmp_P(state, PSTR("on")) == 0)  { Legs::enable();  s_stream->println(F("legs on")); }
    else                                    { Legs::disable(); s_stream->println(F("legs off")); }

  } else if (strcmp_P(command, PSTR("motion")) == 0) {
    const char* state = strtok(nullptr, " ");
    if (state && strcmp_P(state, PSTR("on")) == 0) { Motion::enable();  s_stream->println(F("motion on")); }
    else                                   { Motion::disable(); s_stream->println(F("motion off")); }

  //-- Movement -----------------------------------------------------
  } else if (strcmp_P(command, PSTR("home")) == 0) {
    Legs::home();

  } else if (strcmp_P(command, PSTR("walk")) == 0) {
    const char* steps = strtok(nullptr, " ");
    const char* dir   = strtok(nullptr, " ");
    if (!legsReady()) return;
    float n = steps ? atof(steps) : 1;
    if (dir && dir[0] == 'b') Legs::walkBackward(n); else Legs::walkForward(n);

  } else if (strcmp_P(command, PSTR("turn")) == 0) {
    const char* steps = strtok(nullptr, " ");
    const char* dir   = strtok(nullptr, " ");
    if (!legsReady()) return;
    float n = steps ? atof(steps) : 1;
    if (dir && dir[0] == 'r') Legs::turnRight(n); else Legs::turnLeft(n);

  } else if (strcmp_P(command, PSTR("servo")) == 0) {
    const char* which = strtok(nullptr, " ");
    const char* angleArg = strtok(nullptr, " ");
    if (!which || !angleArg) { s_stream->println(F("servo ll|lr|fl|fr <0-180>")); return; }
    if (!legsReady()) return;
    uint8_t angle = atoi(angleArg);
    if      (strcmp_P(which, PSTR("ll")) == 0) Legs::positionLegLeftDegrees(angle);
    else if (strcmp_P(which, PSTR("lr")) == 0) Legs::positionLegRightDegrees(angle);
    else if (strcmp_P(which, PSTR("fl")) == 0) Legs::positionFootLeftDegrees(angle);
    else if (strcmp_P(which, PSTR("fr")) == 0) Legs::positionFootRightDegrees(angle);
    else s_stream->println(F("servo ll|lr|fl|fr <0-180>"));

  } else if (strcmp_P(command, PSTR("pose")) == 0) {
    const char* a = strtok(nullptr, " "); const char* b = strtok(nullptr, " ");
    const char* c = strtok(nullptr, " "); const char* d = strtok(nullptr, " ");
    const char* ms = strtok(nullptr, " ");
    if (!a || !b || !c || !d) { s_stream->println(F("pose <ll> <lr> <fl> <fr> [ms]")); return; }
    if (!legsReady()) return;
    Legs::positionAllDegrees(atoi(a), atoi(b), atoi(c), atoi(d), ms ? atoi(ms) : 200);

#ifndef OTTOFLOW_CONSOLE_NO_DANCE
  } else if (strcmp_P(command, PSTR("dance")) == 0) {
    const char* name = strtok(nullptr, " ");
    if (!legsReady()) return;
    if (name == nullptr || !danceByName(name)) s_stream->println(F("unknown dance"));
#endif

  } else if (strcmp_P(command, PSTR("bend")) == 0) {
    const char* dir = strtok(nullptr, " ");
    if (!legsReady()) return;
    if (dir && dir[0] == 'r') Legs::bendRight(); else Legs::bendLeft();

  } else if (strcmp_P(command, PSTR("shake")) == 0) {
    const char* dir = strtok(nullptr, " ");
    if (!legsReady()) return;
    if (dir && dir[0] == 'r') Legs::shakeRightLeg(); else Legs::shakeLeftLeg();

  } else if (strcmp_P(command, PSTR("jump")) == 0) {
    if (!legsReady()) return;
    Legs::jump();

#ifdef OTTOFLOW_CONSOLE_GESTURES
  } else if (strcmp_P(command, PSTR("gesture")) == 0) {
    const char* name = strtok(nullptr, " ");
    if (!legsReady()) return;
    if (name == nullptr || !gestureByName(name)) s_stream->println(F("unknown gesture"));
#endif

  //-- Arms ---------------------------------------------------------
  } else if (strcmp_P(command, PSTR("arms")) == 0) {
    const char* action = strtok(nullptr, " ");
    if (action && strcmp_P(action, PSTR("up")) == 0)        { Arms::hold(); Arms::raiseBoth(); }
    else if (action && strcmp_P(action, PSTR("down")) == 0) { Arms::hold(); Arms::lowerBoth(); }
    else                                            { Arms::relax(); s_stream->println(F("arms relaxed")); }
    if (action && !Arms::isActive() && strcmp_P(action, PSTR("off")) != 0) {
      s_stream->println(F("arms not enabled in config"));
    }

  } else if (strcmp_P(command, PSTR("armwave")) == 0) {
    const char* dir = strtok(nullptr, " ");
    Arms::hold();
    if (!Arms::isActive()) { s_stream->println(F("arms not enabled in config")); return; }
    if (dir && dir[0] == 'l') Arms::waveLeft(); else Arms::waveRight();

  //-- Calibration --------------------------------------------------
  } else if (strcmp_P(command, PSTR("trim")) == 0) {
    const char* a = strtok(nullptr, " ");
    if (a && strcmp_P(a, PSTR("save")) == 0) {
      Legs::saveTrimsToEeprom();
      s_stream->println(F("trims saved"));
      return;
    }
    const char* b = strtok(nullptr, " ");
    const char* c = strtok(nullptr, " ");
    const char* d = strtok(nullptr, " ");
    if (!a || !b || !c || !d) { s_stream->println(F("trim <ll> <lr> <fl> <fr> | trim save")); return; }
    Legs::setTrimsDegrees(atoi(a), atoi(b), atoi(c), atoi(d));
    if (legsReady()) Legs::home();   // show the new trim immediately
    s_stream->println(F("trims set (not saved)"));

  } else if (strcmp_P(command, PSTR("version")) == 0) {
    s_stream->println(OttoFlow::version());

  } else {
    s_stream->println(F("unknown command - type 'help'"));
  }
}

void poll() {
  if (s_stream == nullptr) return;
  while (s_stream->available() > 0) {
    char c = (char)s_stream->read();
    if (c == '\r') continue;
    if (c == '\n') {
      s_line[s_length] = '\0';
      if (s_length > 0) handle(s_line);
      s_length = 0;
      return;                      // one command per poll()
    }
    if (s_length < sizeof(s_line) - 1) s_line[s_length++] = c;
  }
}

}  // namespace Console
