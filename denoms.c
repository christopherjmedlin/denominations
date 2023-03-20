#include "denoms.h"
#include <math.h>

const int DENOMS[7] = {1, 2, 5, 10, 20, 50, 100};
const int COIN_DENOMS[4] = {1, 5, 10, 25};

// returns n numbers, each representing the change in the denomination at index
// i in the denoms array. length is the number of denominations
int* get_change(int value, const int* denoms, int length) { 
  int* change = malloc(sizeof(int) * length);

  for (int i = length-1; i >= 0; i--) {
    change[i] = value / denoms[i];
    value %= denoms[i];
  }

  return change;
}

// returns the number before the decimal point in string of format "X*.YY"
int get_dollars(char* str) {
  char* end = str;

  while (*end != '\0' && *end != '.') {
    end++;
  }
  end--;
  int power = 0;
  int value = 0;
  while (end >= str) {
    value += (*end - '0') * pow(10, power);
    end--;
    power++;
  }
  return value;
}

// returns the number after the decimal point in string of format "X*.YY"
int get_coins(char* str) {
  char* end = str;

  while (*end != '\0' && *end != '.') {
    end++;
  }
  if (*end == '\0') return 0;
  // if we are at a decimal point, we can just use get_dollars
  return get_dollars(++end);
}
