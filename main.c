#include <stdio.h>
#include <string.h>

const int DENOMS[7] = {100, 50, 20, 10, 5, 2, 1};
const int COIN_DENOMS[4] = {25, 10, 5, 1};

int main(int argc, char** argv) {
  int dollars = 0, coins = 0;

  printf("Please enter a currency value in the form X.YY\n");
  scanf("%d.%d", &dollars, &coins);
  
  if (coins > 99) {
    printf("Error: precision for cents cannot be greater than 2");
  }
  
  for (int i = 0; i < 7; i++) {
    printf("$%d : %d\n", DENOMS[i], dollars / DENOMS[i]);
    dollars %= DENOMS[i];
  }

  for (int i = 0; i < 4; i++) {
    printf("¢%d : %d\n", COIN_DENOMS[i], coins / COIN_DENOMS[i]);
    coins %= COIN_DENOMS[i];
  }
}
