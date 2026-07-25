#include "ArmServos.h"
#include "../core/Internal.h"
#include <Servo.h>

using ottoflow_internal::config;

namespace ArmServos {

static Servo s_left;
static Servo s_right;
static bool  s_attached = false;

void attach() {
  if (!config().arms.enabled || s_attached) return;
  s_left.attach(config().arms.leftPin);
  s_right.attach(config().arms.rightPin);
  s_attached = true;
}

void detach() {
  if (!s_attached) return;
  s_left.detach();
  s_right.detach();
  s_attached = false;
}

bool isAttached() { return s_attached; }

void positionLeftDegrees(uint8_t angle) {
  if (s_attached) s_left.write(angle > 180 ? 180 : angle);
}

void positionRightDegrees(uint8_t angle) {
  if (s_attached) s_right.write(angle > 180 ? 180 : angle);
}

void positionBothDegrees(uint8_t angle) {
  positionLeftDegrees(angle);
  positionRightDegrees(angle);
}

void positionBothMirroredDegrees(uint8_t angle) {
  if (angle > 180) angle = 180;
  positionLeftDegrees(angle);
  positionRightDegrees(180 - angle);
}

void center() { positionBothDegrees(90); }
void up()     { positionBothMirroredDegrees(180); }
void down()   { positionBothMirroredDegrees(0); }

// Wave angles are written in left-arm terms; the right servo faces the
// other way, so its angles are mirrored to keep both waves identical.
static void waveWith(Servo& servo, uint8_t times, bool mirrored) {
  if (!s_attached) return;
  for (uint8_t i = 0; i < times; i++) {
    servo.write(mirrored ?  20 : 160); delay(300);
    servo.write(mirrored ?  60 : 120); delay(300);
  }
  servo.write(mirrored ? 160 : 20);   // back down
}

void waveRight(uint8_t times) { waveWith(s_right, times, true); }
void waveLeft(uint8_t times)  { waveWith(s_left, times, false); }

}  // namespace ArmServos
