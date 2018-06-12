#include "./cripto.c"
#include <stdio.h>

int main(void) {
  char c;

  for (c = 'A'; c <= 'Z'; ++c) {
    char* str = asciiToMorse(c);
    printf(str);
    printf("\n");
  }
  
  return 0;
}
