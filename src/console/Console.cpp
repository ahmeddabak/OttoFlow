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

#include <string.h>

namespace Console {

static Stream* s_stream = nullptr;
static char    s_line[32];
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
  s_stream->println(F("Commands:"));
  s_stream->println(F("  dist              distance in cm"));
  s_stream->println(F("  touch             touch sensor state"));
  s_stream->println(F("  light             brightness %"));
  s_stream->println(F("  mic               loudness %"));
  s_stream->println(F("  tilt              pitch/roll degrees (MPU-6050)"));
  s_stream->println(F("  face <name>       heart happy smile sad angry surprised"));
  s_stream->println(F("                    confused tongue ok x question line"));
  s_stream->println(F("  digit <0-9>       show a digit"));
  s_stream->println(F("  text <msg>        scroll text"));
  s_stream->println(F("  bright <0-15>     matrix brightness"));
  s_stream->println(F("  clear             blank the matrix"));
  s_stream->println(F("  beep              hello chirp"));
  s_stream->println(F("  sing              happy birthday"));
  s_stream->println(F("  mute | unmute     buzzer on/off"));
  s_stream->println(F("  walk <steps> f|b  walk (needs 'legs on')"));
  s_stream->println(F("  turn <steps> l|r  turn (needs 'legs on')"));
  s_stream->println(F("  home              rest position"));
  s_stream->println(F("  legs on|off       leg servos"));
  s_stream->println(F("  arms up|down|off  arm servos (humanoid builds)"));
  s_stream->println(F("  motion on|off     ALL servos (legs + arms)"));
  s_stream->println(F("  version           framework version"));
}

static bool faceByName(const char* name) {
  struct Entry { const char* name; Icon icon; };
  static const Entry table[] = {
    {"heart", Icon::Heart},         {"happy", Icon::Happy},
    {"smile", Icon::Smile},         {"sad", Icon::Sad},
    {"angry", Icon::Angry},         {"surprised", Icon::Surprised},
    {"confused", Icon::Confused},   {"tongue", Icon::TongueOut},
    {"ok", Icon::Ok},               {"x", Icon::X},
    {"question", Icon::Question},   {"line", Icon::Line},
  };
  for (const Entry& entry : table) {
    if (strcmp(name, entry.name) == 0) {
      Face::show(entry.icon);
      return true;
    }
  }
  return false;
}

static void handle(char* line) {
  char* command = strtok(line, " ");
  if (command == nullptr) return;

  if (strcmp(command, "help") == 0) {
    printHelp();

  } else if (strcmp(command, "dist") == 0) {
    long cm = Eyes::distanceCm();
    if (cm >= Eyes::OUT_OF_RANGE_CM) s_stream->println(F("out of range"));
    else { s_stream->print(cm); s_stream->println(F(" cm")); }

  } else if (strcmp(command, "touch") == 0) {
    s_stream->println(Touch::isTouched() ? F("touched") : F("not touched"));

  } else if (strcmp(command, "light") == 0) {
    s_stream->print(LightSensor::brightnessPercent()); s_stream->println(F(" %"));

  } else if (strcmp(command, "mic") == 0) {
    s_stream->print(Ears::loudnessPercent()); s_stream->println(F(" %"));

  } else if (strcmp(command, "tilt") == 0) {
    if (!Mpu6050::isConnected()) { s_stream->println(F("MPU-6050 not connected/enabled")); return; }
    s_stream->print(F("pitch "));  s_stream->print(Balance::pitchDegrees(), 1);
    s_stream->print(F("  roll ")); s_stream->println(Balance::rollDegrees(), 1);

  } else if (strcmp(command, "face") == 0) {
    const char* name = strtok(nullptr, " ");
    if (name == nullptr || !faceByName(name)) s_stream->println(F("unknown face"));

  } else if (strcmp(command, "digit") == 0) {
    const char* arg = strtok(nullptr, " ");
    if (arg) Face::showDigit(atoi(arg));

  } else if (strcmp(command, "text") == 0) {
    char* message = strtok(nullptr, "");   // rest of the line
    if (message) Face::scrollText(message);

  } else if (strcmp(command, "bright") == 0) {
    const char* arg = strtok(nullptr, " ");
    if (arg) Face::setBrightness(atoi(arg));

  } else if (strcmp(command, "clear") == 0) {
    Face::clear();

  } else if (strcmp(command, "beep") == 0) {
    Voice::play(Sound::Hello);

  } else if (strcmp(command, "sing") == 0) {
    Voice::playHappyBirthday();

  } else if (strcmp(command, "mute") == 0) {
    Voice::mute();  s_stream->println(F("muted"));

  } else if (strcmp(command, "unmute") == 0) {
    Voice::unmute();  s_stream->println(F("unmuted"));

  } else if (strcmp(command, "walk") == 0) {
    const char* steps = strtok(nullptr, " ");
    const char* dir   = strtok(nullptr, " ");
    if (!Legs::isEnabled()) { s_stream->println(F("legs are off - 'legs on' first")); return; }
    float n = steps ? atof(steps) : 1;
    if (dir && dir[0] == 'b') Legs::walkBackward(n); else Legs::walkForward(n);

  } else if (strcmp(command, "turn") == 0) {
    const char* steps = strtok(nullptr, " ");
    const char* dir   = strtok(nullptr, " ");
    if (!Legs::isEnabled()) { s_stream->println(F("legs are off - 'legs on' first")); return; }
    float n = steps ? atof(steps) : 1;
    if (dir && dir[0] == 'r') Legs::turnRight(n); else Legs::turnLeft(n);

  } else if (strcmp(command, "home") == 0) {
    Legs::home();

  } else if (strcmp(command, "legs") == 0) {
    const char* state = strtok(nullptr, " ");
    if (state && strcmp(state, "on") == 0)  { Legs::enable();  s_stream->println(F("legs on")); }
    else                                    { Legs::disable(); s_stream->println(F("legs off")); }

  } else if (strcmp(command, "arms") == 0) {
    const char* action = strtok(nullptr, " ");
    if (action && strcmp(action, "up") == 0)        { Arms::hold(); Arms::raiseBoth(); }
    else if (action && strcmp(action, "down") == 0) { Arms::hold(); Arms::lowerBoth(); }
    else                                            { Arms::relax(); s_stream->println(F("arms relaxed")); }

  } else if (strcmp(command, "motion") == 0) {
    const char* state = strtok(nullptr, " ");
    if (state && strcmp(state, "on") == 0) { Motion::enable();  s_stream->println(F("motion on")); }
    else                                   { Motion::disable(); s_stream->println(F("motion off")); }

  } else if (strcmp(command, "version") == 0) {
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
