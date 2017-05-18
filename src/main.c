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

  DDRE &= ~_BV(PINE4);
  PORTE |= _BV(PINE4);

  EICRB &= ~_BV(ISC40);
  EICRB |= _BV(ISC41);

  physicsModel model = muse_init();

  uint8_t print_orientation(museMotion* m) {
    clearLCD();
    printCharToLCD('X', 0, 0);
    printIntToLCD(m->o.x, 0, 2);

    printCharToLCD('Y', 1, 0);
    printIntToLCD(m->o.y, 1, 2);

    printCharToLCD('Z', 1, 8);
    printIntToLCD(m->o.z, 1, 10);
    _delay_ms(100);

    return NULL;
  }

  uint8_t print_position(museMotion* m) {
    clearLCD();
    printCharToLCD('X', 0, 0);
    printIntToLCD(m->s.x, 0, 2);

    printCharToLCD('Y', 1, 0);
    printIntToLCD(m->s.y, 1, 2);

    printCharToLCD('Z', 1, 8);
    printIntToLCD(m->s.z, 1, 10);
    _delay_ms(100);

    return NULL;
  }

  uint8_t print_accel(museMotion* m) {
    clearLCD();
    printCharToLCD('X', 0, 0);
    printIntToLCD(model.lin_accel.x, 0, 2);

    printCharToLCD('Y', 1, 0);
    printIntToLCD(model.lin_accel.y, 1, 2);

    printCharToLCD('Z', 1, 8);
    printIntToLCD(model.lin_accel.z, 1, 10);
    _delay_ms(100);

    return NULL;
  }

  for(;;) {
    uint8_t (*l)(museMotion* m) = print_orientation;
    if(state == ORIENTATION) {
      l = print_orientation;
    }
    else if(state == POSITION) {
      l = print_position;
    }
    else if(state == ACCEL) {
      l = print_accel;
    }

    muse_detect(200, &model, l);
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
