#include <stdlib.h>

#ifndef DENOMS_H
#define DENOMS_H

extern const int DENOMS[7];
extern const int COIN_DENOMS[4];

int* get_change(int value, const int* denoms, int length);

int get_dollars(char* str);

int get_coins(char* str);

#endif
