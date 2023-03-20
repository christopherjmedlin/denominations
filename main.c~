#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int DENOMS[7] = {100, 50, 20, 10, 5, 2, 1};

int main(int argc, char* argv[]) {
  if (argc == 1) {
    printf("Missing argument\n");
    exit(0);
  }

  int val = atoi(argv[1]);
  printf("%s\n", argv[1]);

  int change[7] = {0,0,0,0,0,0,0};

  for (int i = 0; i < 7; i++) {
    printf("$%d : %d\n", DENOMS[i], val / DENOMS[i]);
    val %= DENOMS[i];
  }
}
