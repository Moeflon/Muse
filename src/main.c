/**
 * @file main.c
 * @brief Muse API functions demo
 * @author Vic Degraeve
 * @author Victor-Louis De Gusseme
 */

#include <avr/io.h>
#include <util/delay.h>

#include "dwenguinoLCD/dwenguinoLCD.h"
#include "museAPI/museAPI.h"

enum { ORIENTATION, POSITION, ACCEL };
uint8_t state = ORIENTATION;

int main(void) {
  initLCD();
  clearLCD();
  backlightOn();

  /* Set up button interrupt */
  DDRE &= ~_BV(PINE4);
  PORTE |= _BV(PINE4);
  EICRB &= ~_BV(ISC40);
  EICRB |= _BV(ISC41);

  /* Initialize Muse */
  physicsModel model = muse_init();

  uint8_t print_muse_info(museMotion* m) {
    clearLCD();

    Vector pr;
    char* s;
    switch(state) {
      case ORIENTATION:
        pr = m->o;
        s = "ORI";
        break;
      case POSITION:
        pr = m->s;
        s = "POS";
        break;
      default:
      case ACCEL:
        pr = m->a;
        s = "ACC";
        break;
    }

    printCharToLCD('X', 0, 0);
    printIntToLCD(pr.x, 0, 2);

    printCharToLCD('Y', 1, 0);
    printIntToLCD(pr.y, 1, 2);

    printCharToLCD('Z', 1, 8);
    printIntToLCD(pr.z, 1, 10);

    for(uint8_t i = 0; i < 3; i++) {
      printCharToLCD(*(s+i), 0, 8 + i);
    }

    _delay_ms(100); /* Don't print too fast */

    return NULL; /* NULL makes the loop continue */
  }

  for(;;) {
    /* Print API information */
    /* After 200 seconds (timout) position will be set to zero */
    muse_detect(200, &model, print_muse_info);
  }
}

ISR(INT4_vect) {
  if(state == ACCEL) {
    state = ORIENTATION;
  }
  else {
    state++;
  }
}
