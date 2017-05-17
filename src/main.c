#include <avr/io.h>
#include <util/delay.h>

#include "dwenguinoLCD/dwenguinoLCD.h"
#include "museAPI/museAPI.h"

int main(void) {
  initLCD();
  clearLCD();
  backlightOn();

  physicsModel model = muse_init();

  enum { SWORD_RIGHT_SLASH = 0, SWORD_LEFT_SLASH, SWORD_RAISE, SWORD_LOWER,
    SWORD_ROT_BACK, SWORD_ROT_FORW, SWORD_RETRACT, SWORD_PROTRACT };

  uint8_t detect_sword_moves(museMotion* m) {
    if(m->s.x > 20 && abs(m->s.z) > 20) return SWORD_RIGHT_SLASH;
    if(m->s.x < 20 && abs(m->s.z) > 20) return SWORD_LEFT_SLASH;

    if(abs(m->s.x) < 10 && m->s.z > 20) return SWORD_RAISE;
    if(abs(m->s.x) < 10 && m->s.z < -20) return SWORD_LOWER;

    if(abs(m->s.z) < 10 && abs(m->s.x) < 10 && m->s.y > 15) return SWORD_PROTRACT;
    if(abs(m->s.z) < 10 && abs(m->s.x) < 10 && m->s.y < -15) return SWORD_RETRACT;

    if(abs(m->s.z) < 10 && abs(m->s.x) < 10 && m->s.y > 15
       && m->o.y > 500) return SWORD_ROT_FORW;

    if(abs(m->s.z) < 10 && abs(m->s.x) < 10 && m->s.y < -15
       && m->o.y < -600) return SWORD_ROT_BACK;
    return NULL;
  }

  uint8_t motion_amt[8]; /* there are 8 types of motions */

  /* In this level (actually the only level in this demo)
     the winning move contains 8 motions */
  for(int i = 0; i < 8;) {
    uint8_t move = muse_detect(2, &model, detect_sword_moves);

    if(move != NULL) {
      motion_amt[move]++;
      i++;
    }
  }

  /* 8 moves have been detected, check if they were the right ones */
  DDRA = 0xFF;
  if(motion_amt[SWORD_RIGHT_SLASH] >= 2
     && motion_amt[SWORD_ROT_BACK] >= 1
     && motion_amt[SWORD_ROT_FORW] >= 1
     && motion_amt[SWORD_RETRACT] >= 1
     && motion_amt[SWORD_PROTRACT] >= 1
     && motion_amt[SWORD_RAISE] >= 1
     && motion_amt[SWORD_LOWER] >= 1) {
       PORTA = 0xFF;
     }
}
