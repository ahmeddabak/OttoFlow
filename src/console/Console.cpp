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
#include "../modules/LightSensor.h"
#include "../modules/ArmServos.h"

#include <string.h>

namespace Console {

static Stream* s_stream = nullptr;
static char    s_line[40];
static uint8_t s_length = 0;

static void printBanner() {
  s_stream->print(F("OttoFlow "));
  s_stream->print(OttoFlow::version());
  s_stream->println(F(" test console - type 'help'"));
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
  s_stream->println(F("  dist touch light mic tilt accel"));
  s_stream->println(F("Matrix:"));
  s_stream->println(F("  face <name>   heart happy smile sad angry surprised"));
  s_stream->println(F("                confused tongue ok x question line"));
  s_stream->println(F("  digit <0-9> | text <msg> | bright <0-15> | clear"));
  s_stream->println(F("Buzzer:"));
  s_stream->println(F("  beep | tone <hz> <ms> | mute | unmute"));
  s_stream->println(F("Motors (enable first!):"));
  s_stream->println(F("  legs on|off | motion on|off | home"));
  s_stream->println(F("  servo ll|lr|fl|fr <0-180>      one leg servo"));
  s_stream->println(F("  pose <ll> <lr> <fl> <fr> [ms]  all four"));
  s_stream->println(F("  arm l|r <0-180>                one arm servo"));
  s_stream->println(F("  arms on|off                    hold / relax arms"));
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

// Motor commands need the leg servos enabled.
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

  //-- Buzzer -------------------------------------------------------
  } else if (strcmp_P(command, PSTR("beep")) == 0) {
    Voice::play(Sound::Hello);

  } else if (strcmp_P(command, PSTR("tone")) == 0) {
    const char* hz = strtok(nullptr, " ");
    const char* ms = strtok(nullptr, " ");
    if (hz && ms) Voice::playToneHz(atoi(hz), atoi(ms));
    else s_stream->println(F("tone <hz> <ms>"));

  } else if (strcmp_P(command, PSTR("mute")) == 0) {
    Voice::mute();  s_stream->println(F("muted"));

  } else if (strcmp_P(command, PSTR("unmute")) == 0) {
    Voice::unmute();  s_stream->println(F("unmuted"));

  //-- Motor switches -----------------------------------------------
  } else if (strcmp_P(command, PSTR("legs")) == 0) {
    const char* state = strtok(nullptr, " ");
    if (state && strcmp_P(state, PSTR("on")) == 0)  { Legs::enable();  s_stream->println(F("legs on")); }
    else                                            { Legs::disable(); s_stream->println(F("legs off")); }

  } else if (strcmp_P(command, PSTR("motion")) == 0) {
    const char* state = strtok(nullptr, " ");
    if (state && strcmp_P(state, PSTR("on")) == 0) { Motion::enable();  s_stream->println(F("motion on")); }
    else                                           { Motion::disable(); s_stream->println(F("motion off")); }

  //-- Individual motors --------------------------------------------
  } else if (strcmp_P(command, PSTR("home")) == 0) {
    if (legsReady()) Legs::home();

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

  } else if (strcmp_P(command, PSTR("arm")) == 0) {
    const char* side = strtok(nullptr, " ");
    const char* angleArg = strtok(nullptr, " ");
    if (!side || !angleArg) { s_stream->println(F("arm l|r <0-180>")); return; }
    ArmServos::attach();
    if (!Arms::isActive()) { s_stream->println(F("arms not enabled in config")); return; }
    uint8_t angle = atoi(angleArg);
    if (side[0] == 'l') ArmServos::positionLeftDegrees(angle);
    else                ArmServos::positionRightDegrees(angle);

  } else if (strcmp_P(command, PSTR("arms")) == 0) {
    const char* state = strtok(nullptr, " ");
    if (state && strcmp_P(state, PSTR("on")) == 0) {
      Arms::hold();
      s_stream->println(Arms::isActive() ? F("arms on") : F("arms not enabled in config"));
    } else {
      Arms::relax();
      s_stream->println(F("arms relaxed"));
    }

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
