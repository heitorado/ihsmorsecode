#include "./cripto.c"
#include <stdio.h>

int main(void) {
  char c;

  for (c = 'A'; c <= 'Z'; ++c) {
    char* str = asciiToMorse(c);
    printf(str);

    char foo = morseToAscii(str);    
    printf("    %c\n", foo);
  }
  
  return 0;
}
