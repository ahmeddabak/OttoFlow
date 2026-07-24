#include "Console.h"
#include "../core/OttoCore.h"
#include "../facades/Face.h"
#include "../facades/Eyes.h"
#include "../facades/Voice.h"
#include "../facades/Legs.h"
#include "../facades/Arms.h"
#include "../facades/Motion.h"

#include <string.h>

namespace Console {

static char    s_line[32];
static uint8_t s_length = 0;

void begin(unsigned long baud) {
  Serial.begin(baud);
  Serial.print(F("OttoFlow "));
  Serial.print(OttoFlow::version());
  Serial.println(F(" console - type 'help'"));
}

static void printHelp() {
  Serial.println(F("Commands:"));
  Serial.println(F("  dist              distance in cm"));
  Serial.println(F("  face <name>       heart happy smile sad angry surprised"));
  Serial.println(F("                    confused tongue ok x question line"));
  Serial.println(F("  digit <0-9>       show a digit"));
  Serial.println(F("  text <msg>        scroll text"));
  Serial.println(F("  bright <0-15>     matrix brightness"));
  Serial.println(F("  clear             blank the matrix"));
  Serial.println(F("  beep              hello chirp"));
  Serial.println(F("  mute | unmute     buzzer on/off"));
  Serial.println(F("  walk <steps> f|b  walk (needs 'legs on')"));
  Serial.println(F("  turn <steps> l|r  turn (needs 'legs on')"));
  Serial.println(F("  home              rest position"));
  Serial.println(F("  legs on|off       enable/disable leg servos"));
  Serial.println(F("  arms up|down|off  arm servos (humanoid builds)"));
  Serial.println(F("  motion on|off     ALL servos (legs + arms)"));
  Serial.println(F("  version           framework version"));
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
    if (cm >= Eyes::OUT_OF_RANGE_CM) Serial.println(F("out of range"));
    else { Serial.print(cm); Serial.println(F(" cm")); }

  } else if (strcmp(command, "face") == 0) {
    const char* name = strtok(nullptr, " ");
    if (name == nullptr || !faceByName(name)) Serial.println(F("unknown face"));

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

  } else if (strcmp(command, "mute") == 0) {
    Voice::mute();  Serial.println(F("muted"));

  } else if (strcmp(command, "unmute") == 0) {
    Voice::unmute();  Serial.println(F("unmuted"));

  } else if (strcmp(command, "walk") == 0) {
    const char* steps = strtok(nullptr, " ");
    const char* dir   = strtok(nullptr, " ");
    if (!Legs::isEnabled()) { Serial.println(F("legs are off - 'legs on' first")); return; }
    float n = steps ? atof(steps) : 1;
    if (dir && dir[0] == 'b') Legs::walkBackward(n); else Legs::walkForward(n);

  } else if (strcmp(command, "turn") == 0) {
    const char* steps = strtok(nullptr, " ");
    const char* dir   = strtok(nullptr, " ");
    if (!Legs::isEnabled()) { Serial.println(F("legs are off - 'legs on' first")); return; }
    float n = steps ? atof(steps) : 1;
    if (dir && dir[0] == 'r') Legs::turnRight(n); else Legs::turnLeft(n);

  } else if (strcmp(command, "home") == 0) {
    Legs::home();

  } else if (strcmp(command, "legs") == 0) {
    const char* state = strtok(nullptr, " ");
    if (state && strcmp(state, "on") == 0)  { Legs::enable();  Serial.println(F("legs on")); }
    else                                    { Legs::disable(); Serial.println(F("legs off")); }

  } else if (strcmp(command, "arms") == 0) {
    const char* action = strtok(nullptr, " ");
    if (action && strcmp(action, "up") == 0)        { Arms::hold(); Arms::raiseBoth(); }
    else if (action && strcmp(action, "down") == 0) { Arms::hold(); Arms::lowerBoth(); }
    else                                            { Arms::relax(); Serial.println(F("arms relaxed")); }

  } else if (strcmp(command, "motion") == 0) {
    const char* state = strtok(nullptr, " ");
    if (state && strcmp(state, "on") == 0) { Motion::enable();  Serial.println(F("motion on")); }
    else                                   { Motion::disable(); Serial.println(F("motion off")); }

  } else if (strcmp(command, "version") == 0) {
    Serial.println(OttoFlow::version());

  } else {
    Serial.println(F("unknown command - type 'help'"));
  }
}

void poll() {
  while (Serial.available() > 0) {
    char c = (char)Serial.read();
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
