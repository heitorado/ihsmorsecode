#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <time.h>
#include <omp.h>

// Referecing the 4 pushbuttons from the FPGA, from left to right.
#define BT1 8
#define BT2 4
#define BT3 2
#define BT4 1

// Referencing the 18 switches from the FPGA, from left to right.

#define SW18 131072
#define SW17 65536
#define SW16 32768
#define SW15 16384
#define SW14 8192
#define SW13 4096
#define SW12 2048
#define SW11 1024
#define SW10 512
#define SW09 256
#define SW08 128
#define SW07 64
#define SW06 32
#define SW05 16
#define SW04 8
#define SW03 4
#define SW02 2
#define SW01 1

// Constraints for morse code
#define MAX_DOT_TIME 50000

// Conversion array for 7 Segment display.
unsigned char hexdigit[] = {0x3F, 0x06, 0x5B, 0x4F,
                            0x66, 0x6D, 0x7D, 0x07, 
                            0x7F, 0x6F, 0x77, 0x7C,
                            0x39, 0x5E, 0x79, 0x71};


unsigned long int readSwitch(int dev, long int *k)
{
    unsigned long int sw;
    read(dev, k, 0);
    *k &= 0x3FFFF;
    sw = *k;

    return sw;
}

unsigned long int readButton(int dev, long int *k)
{
    unsigned long int bt;
    read(dev, k, 1);
    *k &= 0xF;
    bt = *k;
    bt = abs(bt-15);

    return bt;
}

void writeDisplayRight(int num1, int num2, int num3, int num4, int dev)
{
  long int i = 10;
  long int k = 0;

  k = hexdigit[num4];
  k = k | hexdigit[num3] << 8;
  k = k | hexdigit[num2] << 16;
  k = k | hexdigit[num1] << 24;
  k = ~k;

  while(i>0){
    write(dev, &k, 0);
    //write(dev, &k, 1);
    --i;
  }
  return;
}

void writeDisplayLeft(int num1, int num2, int num3, int num4, int dev)
{
  long int i = 10;
  long int k = 0;

  k = hexdigit[num4];
  k = k | hexdigit[num3] << 8;
  k = k | hexdigit[num2] << 16;
  k = k | hexdigit[num1] << 24;
  k = ~k;

  while(i>0){
    //write(dev, &k, 0);
    write(dev, &k, 1);
    --i;
  }
  return;
}

void writeRedLeds(int val, int dev)
{
  int leds = val;
  write(dev, &leds, 2);

  return;
}

void writeGreenLeds(int val, int dev)
{
  int leds = val;
  write(dev, &leds, 3);

  return;
}


int main() {

  // Initial Setup
  srand(time(NULL));

  unsigned long int sw=0, bt=0;             // for reading switches and buttons
  unsigned long int test;
  long int i=0, j=0, k=0, l=0; // aux
  

  //threads
  int tid;

  //app specific
  char morseCode[5];      // for storing dots and slashes
  char text[100000];      // for storing the message.
  int tempo = 0;
  int pontos = 0, tracos = 0;


  int dev = open("/dev/de2i150_altera", O_RDWR);
  //printf("dev ID: %d\n", dev);
  //TODO - Create thread for decoding morse
  int maxt=0;

  /*#pragma omp parallel num_threads(2) private(tid)
  {
    tid = omp_get_thread_num();

    if(tid != 0) //thread responsavel por ler o caractere morse
    {
      //while(1){}
      printf("sou a thread %d\n", tid);
    }

    #pragma omp master
    {*/

    int prog = 1;
      while(prog)
      {
        bt = readButton(dev, &k);
        //printf("bt: %d\n", bt);
        while(bt == BT1){
          bt = readButton(dev, &k);
          tempo++;
          //printf("tempo dentro do while: %d\n", tempo);
        }

        if(bt == 0)
        {
          //printf("tempo: %d\n", tempo);
          if(tempo > MAX_DOT_TIME) //traco
          {
            writeDisplayRight(1, 1, 1, 1, dev);
            tracos++;
            tempo = 0;
          }
          else if(tempo > 0 && tempo <= MAX_DOT_TIME)
          {
            writeDisplayRight(0, 0, 0, 0, dev);
            pontos++;
            tempo = 0;

          }

        }
    /*  }
    }*/
        sw = readSwitch(dev, &k);
        //printf("asgasg%lu\n", sw);
        if(sw == SW07)
          prog = 0;

  }

  printf("fim do programa\n");
  printf("li %d pontos e %d tracos\n", pontos, tracos);

  return 0;
}

  /*
  // Main program
  while(1)
  {
    // Reads serial input from arduino

    // Converts to - or .

    // Bips the buzzer accordingly (ASM - C integration)

    // Every 1.5 seconds, the conversion thread made in OPENMP will empty the dot-slash vector and convert to a character.

    // If the 'finish' button/switch is active, read the current switch state and apply the corresponding criptography on text vector, saving it to a file afterwards.
    

    sw = readSwitch(dev, &k);
    printf("SW: %lu\n", sw);


    bt = readButton(dev, &k);
    printf("BT: %lu\n", bt);


    

    sleep(1);

    writeDisplayLeft(1,1,1,1,dev);
    writeDisplayRight(5,5,5,5,dev);

    writeRedLeds(0x55, dev);
    writeGreenLeds(0x0, dev);

    // Besides all that, the application should respond the pushbutton command to erase a character from text vector.
  }

  //close(dev);
  return 0;
}
*/

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

