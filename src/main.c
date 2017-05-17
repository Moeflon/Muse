#include <util/delay.h>

#include "dwenguinoLCD/dwenguinoLCD.h"
#include "museAPI/museAPI.h"

int main(void) {
  initLCD();
  clearLCD();
  backlightOn();

  physicsModel model = muse_init();

  uint8_t detect_my_cool_moves(museMotion* m) {
    if(m->v > 64) { /* holy shitballs 1 m/s that is fast mayne */ return 1; }
  }

  for(;;) {
    uint8_t move = muse_detect(10, &model, detect_my_cool_moves);
  }
}
