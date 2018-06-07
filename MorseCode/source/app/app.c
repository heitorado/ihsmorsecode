#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <time.h>

// Referecing the 4 pushbuttons from the FPGA, from left to right.
#define BT1 8
#define BT2 4
#define BT3 2
#define BT4 1

// Referencing the 18 switches from the FPGA, from left to right.

#define SW18 0
#define SW17 0
#define SW16 0
#define SW15 0
#define SW14 0
#define SW13 0
#define SW12 0
#define SW11 0
#define SW10 0
#define SW09 0
#define SW08 0
#define SW07 0
#define SW06 0
#define SW05 0
#define SW04 0
#define SW03 0
#define SW02 0
#define SW01 0

// Conversion array for 7 Segment display.
unsigned char hexdigit[] = {0x3F, 0x06, 0x5B, 0x4F,
                            0x66, 0x6D, 0x7D, 0x07, 
                            0x7F, 0x6F, 0x77, 0x7C,
                            0x39, 0x5E, 0x79, 0x71};


int main() {

  // Initial Setup
  srand(time(NULL));

  int disp1, disp2;       // for writing on 7 seg displays
  int rLeds, gLeds;       // for writing on red and green leds
  unsigned long int sw, bt;             // for reading switches and buttons
  unsigned long int test;
  long int i=0, j=0, k=0, l=0; // aux
  char aux;
  char morseCode[5];      // for storing dots and slashes
  char text[100000];      // for storing the message.


  int dev = open("/dev/de2i150_altera", O_RDWR);
  printf("dev ID: %d\n", dev);
  puts("aa");

  //TODO - Create thread for decoding morse

  // Main program
  gLeds = 0x1;
  while( 1 )
  {
    // Reads serial input from arduino

    // Converts to - or .

    // Bips the buzzer accordingly (ASM - C integration)

    // Every 1.5 seconds, the conversion thread made in OPENMP will empty the dot-slash vector and convert to a character.

    // If the 'finish' button/switch is active, read the current switch state and apply the corresponding criptography on text vector, saving it to a file afterwards.
    
    puts("oi");

    read(dev, &k, 0);
    k &= 0x3FFFF;
    sw = k;
    printf("SW: %lu\n", sw);

    read(dev, &k, 1);
    k &= 0xF;
    bt = k;
    printf("BT: %lu\n", bt);


    

    sleep(1);

      i = 10;

      k = hexdigit[rand()%10];
      k = k | hexdigit[rand()%10] << 8;
      k = k | hexdigit[rand()%10] << 16;
      k = k | hexdigit[rand()%10] << 24;
      k = ~k;

      while(i>0){
        write(dev, &k, 0);
        write(dev, &k, 1);
        --i;
      }

      if(sw == 128)
      {
        
        write(dev, &gLeds, 2);
        write(dev, &gLeds, 3);

        printf("Valor nos leds: %d\n", gLeds);
        gLeds++;
      }

    // Besides all that, the application should respond the pushbutton command to erase a character from text vector.
  }

  //close(dev);
  return 0;
}

/* QUICK REF:

READING SWITCHES:
  read(dev, &k, 0);
  sw = k & 0xFF;

READING BUTTONS:
  read(dev, &k, 1);
  bt = k & 0xFF;
  bt = abs(bt-15);

WRITING ON 7-SEG DISPLAY
  disp1 = hexdigit[ <decimal number> ];
  disp1 = disp1 | hexdigit[ <decimal number> ] << 8;
  disp1 = disp1 | hexdigit[ <decimal number> ] << 16;
  disp1 = disp1 | hexdigit[ <decimal number> ] << 24;
  disp1 = ~disp1;

  Display on the Left:
    write(dev, &disp1, 1);
  Display on the Right:
    write(dev, &disp1, 0);

  (USUALLY IS BETTER WRITING SEVERAL TIMES (JUST TO BE SURE))

WRITING ON LEDS
  write(dev, &rLeds, 3)
  write(dev, &gLeds, 2)
  
*/

