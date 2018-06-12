#pragma once

#include <stdbool.h>
#include <string.h>

// Client functions //

char morseToAscii(char* morseChar); // converts a morse character into a ascii char 
char* asciiToMorse(char ascii); // converts a ascii char into a morse character



// Internal functions //
char toUpper(char lower);
bool isUpper(char c);
bool isLower(char c);

int findAscii(char ascii); // return index of a given ascii if found it was found in dict[], if it was not found, then return < 0
int findMorse(char* morse); // return index of a given morse if found it was found in dict[]

struct DictionaryEntry {
  char ascii;
  char morse[5];
};

typedef struct DictionaryEntry DictionaryEntry;

DictionaryEntry dict[] = {
				{' ', " "},
				{'A', ".-"},
				{'B', "-..."},
				{'C', "-.-."},
				{'D', "-.."},
				{'E', "."},
				{'F', "..-."},
				{'G', "--."},
				{'H', "...."},
				{'I', ".."},
				{'J', ".---"},
				{'K', "-.-"},
				{'L', ".-.."},
				{'M', "--"},
				{'N', "-."},
				{'O', "---"},
				{'P', ".--."},
				{'Q', "--.-"},
				{'R', ".-."},
				{'S', "..."},
				{'T', "-"},
				{'U', "..-"},
				{'V', "...-"},
				{'W', ".--"},
				{'X', "-..-"},
				{'Y', "-.--"},
				{'Z', "--.."},
				{'\0', "\0"}
};

