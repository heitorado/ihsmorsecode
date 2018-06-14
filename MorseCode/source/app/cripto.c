#include "./cripto.h"

char morseToAscii(char* morseChar) { // converts a morse character into a ascii char 
  int index = findMorse(morseChar);

  if (index >= 0)  
    return dict[ index ].ascii;
  else
    return '#';
}

char* asciiToMorse(char ascii) { // converts a ascii char into a morse character
  int index;
  
  if (ascii == ' ')
    return dict[0].morse;
  else if (isLower(ascii))
    ascii = toUpper(ascii);
  else if ( ! isUpper(ascii) )
    return NULL;

  index = findAscii(ascii);

  if (index >= 0)
    return dict[ index ].morse;
  else
    return "####";
}

char cesar(unsigned long int key, char asciiUpper) {
  key = key % 26;

  return 'A' + ( (asciiUpper - 'A' + key) % 26 );
}

char kevin(unsigned long int key, char asciiUpper, bool direction) {
  key = key % 26;

  if (direction) {
    return cesar(key, asciiUpper);
  } else {
    return cesar(26 - key, asciiUpper);
  }
}


char toUpper(char lower) {
  return lower + 'A' - 'a';
}

bool isUpper(char c) {
  if (c >= 'A' && c <= 'Z')
    return true;
  else
    return false;
}

bool isLower(char c) {
  if (c >= 'a' && c <= 'z')
    return true;
  else
    return false;
}

int findAscii(char ascii) {
  int i;

  for (i = 0; dict[i].ascii != '\0'; ++i) {
    if (dict[i].ascii == ascii) {
      return i;
    }
  }

  return -1;
}

int findMorse(char* morse) {
  int i;

  for (i = 0; strcmp("\0", dict[i].morse); ++i) {
    if (strcmp(morse, dict[i].morse) == 0) {
      return i;
    }
  }

  return -1;
}