#include "AppLink.h"
#include "../core/Internal.h"
#include "Bluetooth.h"
#include "Matrix.h"
#include "Buzzer.h"
#include "LegServos.h"
#include <Otto.h>
#include <stdlib.h>
#include <string.h>

using ottoflow_internal::drv;

namespace AppLink {

static Stream* s_stream = nullptr;

//-- Movement state: the app sets a move, we repeat it until S ------
static int s_moveId   = 0;
static int s_periodMs = 1000;
static int s_moveSize = 15;

static void sendAck()      { delay(30); s_stream->println(F("&&A%%")); }
static void sendFinalAck() { delay(30); s_stream->println(F("&&F%%")); }

static int nextInt(bool& ok) {
  char* arg = strtok(nullptr, " ");
  if (arg == nullptr) { ok = false; return 0; }
  return atoi(arg);
}

//-- One cycle of the currently selected movement (app ids 0..20) ---
static void runCurrentMove() {
  switch (s_moveId) {
    case 0:  LegServos::home(); break;
    case 1:  LegServos::walk(1, s_periodMs, 1); break;
    case 2:  LegServos::walk(1, s_periodMs, -1); break;
    case 3:  LegServos::turn(1, s_periodMs, 1); break;
    case 4:  LegServos::turn(1, s_periodMs, -1); break;
    case 5:  LegServos::upDown(1, s_periodMs, s_moveSize); break;
    case 6:  LegServos::moonwalk(1, s_periodMs, s_moveSize, 1); break;
    case 7:  LegServos::moonwalk(1, s_periodMs, s_moveSize, -1); break;
    case 8:  LegServos::swing(1, s_periodMs, s_moveSize); break;
    case 9:  LegServos::crusaito(1, s_periodMs, s_moveSize, 1); break;
    case 10: LegServos::crusaito(1, s_periodMs, s_moveSize, -1); break;
    case 11: LegServos::jump(1, s_periodMs); break;
    case 12: LegServos::flap(1, s_periodMs, s_moveSize, 1); break;
    case 13: LegServos::flap(1, s_periodMs, s_moveSize, -1); break;
    case 14: LegServos::tiptoeSwing(1, s_periodMs, s_moveSize); break;
    case 15: LegServos::bend(1, s_periodMs, 1); break;
    case 16: LegServos::bend(1, s_periodMs, -1); break;
    case 17: LegServos::shakeLeg(1, s_periodMs, 1); break;
    case 18: LegServos::shakeLeg(1, s_periodMs, -1); break;
    case 19: LegServos::jitter(1, s_periodMs, s_moveSize); break;
    case 20: LegServos::ascendingTurn(1, s_periodMs, s_moveSize); break;
    default: return;                 // manual servo mode: nothing to repeat
  }
  sendFinalAck();
}

//-- App id tables (same order as the official firmware) ------------
static const Gesture GESTURES[] = {
  Gesture::Happy, Gesture::SuperHappy, Gesture::Sad, Gesture::Sleeping,
  Gesture::Fart, Gesture::Confused, Gesture::Love, Gesture::Angry,
  Gesture::Fretful, Gesture::Magic, Gesture::Wave, Gesture::Victory,
  Gesture::Fail
};
static const Sound SOUNDS[] = {
  Sound::Hello, Sound::Goodbye, Sound::Surprise, Sound::OhOoh,
  Sound::OhOoh2, Sound::Cuddly, Sound::Sleeping, Sound::Happy,
  Sound::SuperHappy, Sound::HappyShort, Sound::Sad, Sound::Confused,
  Sound::Fart1, Sound::Fart2, Sound::Fart3, Sound::Mode1,
  Sound::Mode2, Sound::Mode3, Sound::ButtonPushed
};

static void handleLine(char* line) {
  char* command = strtok(line, " ");
  if (command == nullptr) return;
  bool ok = true;

  switch (command[0]) {
    case 'S': {                                  // stop
      sendAck();
      s_moveId = 0;
      LegServos::home();
      sendFinalAck();
      break;
    }
    case 'M': {                                  // movement <id> [period] [size]
      sendAck();
      if (drv().getRestState()) drv().setRestState(false);
      s_moveId = nextInt(ok);
      if (!ok) { s_moveId = 0; break; }
      bool hasT = true;   int t = nextInt(hasT);   s_periodMs = hasT ? t : 1000;
      bool hasS = true;   int z = nextInt(hasS);   s_moveSize = hasS ? z : 15;
      break;                                     // final ack after each cycle
    }
    case 'H': {                                  // gesture <1..13>
      sendAck();
      LegServos::home();
      int id = nextInt(ok);
      if (ok && id >= 1 && id <= (int)(sizeof(GESTURES) / sizeof(GESTURES[0]))) {
        LegServos::playGesture(GESTURES[id - 1]);
      }
      sendFinalAck();
      break;
    }
    case 'K': {                                  // sound <1..19>
      sendAck();
      LegServos::home();
      int id = nextInt(ok);
      if (ok && id >= 1 && id <= (int)(sizeof(SOUNDS) / sizeof(SOUNDS[0]))) {
        Buzzer::play(SOUNDS[id - 1]);
      }
      sendFinalAck();
      break;
    }
    case 'L': {                                  // matrix <binary pattern>
      sendAck();
      LegServos::home();
      char* arg = strtok(nullptr, " ");
      if (arg != nullptr) Matrix::drawPattern(strtoul(arg, nullptr, 2));
      sendFinalAck();
      break;
    }
    case 'T': {                                  // tone <frequencyHz> <durationMs>
      sendAck();
      LegServos::home();
      int frequency = nextInt(ok);
      int duration  = nextInt(ok);
      if (ok) Buzzer::playToneHz(frequency, duration, 1);
      sendFinalAck();
      break;
    }
    case 'C': {                                  // calibrate <yl> <yr> <rl> <rr>
      sendAck();
      LegServos::home();
      int yl = nextInt(ok), yr = nextInt(ok), rl = nextInt(ok), rr = nextInt(ok);
      if (ok) {
        LegServos::setTrimsDegrees(yl, yr, rl, rr);
        LegServos::saveTrimsToEeprom();
      }
      sendFinalAck();
      break;
    }
    case 'G': {                                  // direct servo <yl> <yr> <rl> <rr>
      sendAck();
      s_moveId = 30;                             // manual mode: stop auto-repeat
      int yl = nextInt(ok), yr = nextInt(ok), rl = nextInt(ok), rr = nextInt(ok);
      if (ok && LegServos::isEnabled()) {
        int positions[4] = {yl, yr, rl, rr};
        drv()._moveServos(200, positions);
      }
      sendFinalAck();
      break;
    }
    default: {                                   // unknown: behave like stop
      sendAck();
      s_moveId = 0;
      LegServos::home();
      sendFinalAck();
      break;
    }
  }
}

void begin()               { Bluetooth::begin(); s_stream = &Bluetooth::stream(); }
void begin(Stream& stream) { s_stream = &stream; }

void poll() {
  if (s_stream == nullptr) return;

  static char    line[40];
  static uint8_t length = 0;

  while (s_stream->available() > 0) {
    char c = (char)s_stream->read();
    if (c == '\r' || c == '\n') {
      if (length > 0) {
        line[length] = '\0';
        length = 0;
        handleLine(line);
      }
    } else if (length < sizeof(line) - 1) {
      line[length++] = c;
    }
  }

  // Keep the selected movement running until the app sends S.
  if (!drv().getRestState()) runCurrentMove();
}

}  // namespace AppLink
