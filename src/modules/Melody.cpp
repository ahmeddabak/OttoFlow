#include "Melody.h"
#include "Buzzer.h"

namespace Melody {

void playHz(const uint16_t* notesHz, const uint8_t* beats,
            uint8_t noteCount, uint16_t tempoMs) {
  for (uint8_t i = 0; i < noteCount; i++) {
    uint16_t frequency = pgm_read_word(&notesHz[i]);
    uint8_t  beat      = pgm_read_byte(&beats[i]);
    long duration = (long)beat * tempoMs;

    if (frequency == 0) {
      delay(duration);                         // rest
    } else {
      Buzzer::playToneHz(frequency, duration, 0);
    }
    delay(tempoMs / 2);                        // small gap between notes
  }
}

//-- Happy Birthday (as in the official Otto_happybirthday example)
static const uint16_t HB_NOTES[] PROGMEM = {
  392, 392, 440, 392, 523, 494,        // Hap-py birth-day to you
  392, 392, 440, 392, 587, 523,        // Hap-py birth-day to you
  392, 392, 784, 659, 523, 494, 440,   // Hap-py birth-day dear Ot-to
  698, 698, 659, 523, 587, 523         // Hap-py birth-day to you
};
static const uint8_t HB_BEATS[] PROGMEM = {
  1, 1, 2, 2, 2, 4,
  1, 1, 2, 2, 2, 4,
  1, 1, 2, 2, 2, 2, 4,
  1, 1, 2, 2, 2, 4
};

void playHappyBirthday() {
  playHz(HB_NOTES, HB_BEATS, sizeof(HB_BEATS), 150);
}

}  // namespace Melody
