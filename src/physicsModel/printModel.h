#include "physicsModel.h"
#include "dwenguinoLCD/dwenguinoLCD.h"

void printModel(physicsModel* model, uint8_t state);
void printVector(Vector*, char[], uint8_t str_size);
void printVector32(Vector32*, uint8_t shift, char[], uint8_t str_size);
