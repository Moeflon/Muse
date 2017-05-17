#include "printModel.h"

void printModel(physicsModel* model, uint8_t state){

  switch(state){
    case 0: printVector32(&(model->position_raw), 8, "POS_CM", 6);
    case 1: printVector(&(model->orientation_deg), "ORIENT", 6);
  }
}

void printVector(Vector* v, char s[], uint8_t str_size){
  clearLCD();
  printCharToLCD('X', 0, 0);
  printIntToLCD(v->x, 0, 2);

  printCharToLCD('Y', 1, 0);
  printIntToLCD(v->y, 1, 2);

  printCharToLCD('Z', 1, 8);
  printIntToLCD(v->z, 1, 10);

  for(uint8_t i = 0; i < str_size; i++){
  printCharToLCD(*(s+i), 0, 8+i);
  }
}
void printVector32(Vector32* v, uint8_t shift, char s[], uint8_t str_size){

}
