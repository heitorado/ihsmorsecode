#include <unistd.h>

#include <fcntl.h>
#include <stdio.h>
#include <time.h>
#include <omp.h>
#include "./cripto.c"
// CPP INCLUDES
//#include <cstdlib>
//#include <cmath>
//#include <iostream>
//using namespace std;
//

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

//VARIAVEIS GLOBAIS
int n1=0,n2=0,n3=0,n4,n5=0,n6=0,n7=0,n8=0,palavras=0,tamanho=0;
int globalCounter=0;
char morseCode[100]={'\0'};      // for storing dots and slashes
char text[10000];      // for storing the message.
//text = malloc(100000*sizeof(char));
long int tempo = 0, tempo2 = 0, tempo3 = 0;

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

  k = num4;
  k = k | num3 << 8;
  k = k | num2 << 16;
  k = k | num1 << 24;
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
void Intensity(int n, int dev)
{
  sleep(1);
  if(n == 0){ writeGreenLeds(0x0,dev); writeRedLeds(0x0, dev); }
  else if(n<=MAX_DOT_TIME/8) writeGreenLeds(1,dev);
  else if(n<=2*MAX_DOT_TIME/8) writeGreenLeds(3,dev);
  else if(n<=3*MAX_DOT_TIME/8) writeGreenLeds(7,dev);
  else if(n<=4*MAX_DOT_TIME/8) writeGreenLeds(15,dev);
  else if(n<=5*MAX_DOT_TIME/8) writeGreenLeds(31,dev);
  else if(n<=6*MAX_DOT_TIME/8) writeGreenLeds(63,dev);
  else if(n<=7*MAX_DOT_TIME/8) writeGreenLeds(127,dev);
  else if(n<=8*MAX_DOT_TIME/8) writeGreenLeds(255,dev);
  else if(n<=9*MAX_DOT_TIME/8) {writeGreenLeds(255,dev); writeRedLeds(1,dev);}
  else if(n<=10*MAX_DOT_TIME/8) {writeGreenLeds(255,dev); writeRedLeds(3,dev);}
  else if(n<=11*MAX_DOT_TIME/8) {writeGreenLeds(255,dev); writeRedLeds(7,dev);}
  else if(n<=12*MAX_DOT_TIME/8) {writeGreenLeds(255,dev); writeRedLeds(15,dev);}
  else if(n<=13*MAX_DOT_TIME/8) {writeGreenLeds(255,dev); writeRedLeds(31,dev);}
  else if(n<=14*MAX_DOT_TIME/8) {writeGreenLeds(255,dev); writeRedLeds(63,dev);}
  else if(n<=15*MAX_DOT_TIME/8) {writeGreenLeds(255,dev); writeRedLeds(127,dev);}
  else if(n<=16*MAX_DOT_TIME/8) {writeGreenLeds(255,dev); writeRedLeds(255,dev);}
  else if(n<=17*MAX_DOT_TIME/8) {writeGreenLeds(255,dev); writeRedLeds(511,dev);}
  else if(n<=18*MAX_DOT_TIME/8) {writeGreenLeds(255,dev); writeRedLeds(1023,dev);}
  else if(n<=19*MAX_DOT_TIME/8) {writeGreenLeds(255,dev); writeRedLeds(2047,dev);}
  else if(n<=20*MAX_DOT_TIME/8) {writeGreenLeds(255,dev); writeRedLeds(4095,dev);}
  else if(n<=21*MAX_DOT_TIME/8) {writeGreenLeds(255,dev); writeRedLeds(8191,dev);}
  else if(n<=22*MAX_DOT_TIME/8) {writeGreenLeds(255,dev); writeRedLeds(16383,dev);}
  else if(n<=23*MAX_DOT_TIME/8) {writeGreenLeds(255,dev); writeRedLeds(32767,dev);}
  else if(n<=24*MAX_DOT_TIME/8) {writeGreenLeds(255,dev); writeRedLeds(65535,dev);}
  else if(n<=25*MAX_DOT_TIME/8) {writeGreenLeds(255,dev); writeRedLeds(131071,dev);}
  else if(n<=26*MAX_DOT_TIME/8) {writeGreenLeds(255,dev); writeRedLeds(262143,dev);}
  return;
}
void NumberToDisplay(int n, int dev)
{
  n1 = n/10;
  n2 = n%10;
  writeDisplayLeft(n1,n2,n3,n4, dev);

}
void count(int dev)
{
  int i;
  char morse[10];
  for(i=8;i>=0;i--){
      n4=i;
      writeDisplayLeft(n1,n2,n3,n4, dev);
      sleep(1);
  }
  globalCounter=0;
  n5=128;
  n6=128;
  n7=128;
  n8=128;
  writeDisplayRight(n5,n6,n7,n8, dev);
  for(i=0;i<4;i++) {
    morse[i] = morseCode[i];
    morseCode[i] = '\0';
  }
  text[tamanho] = morseToAscii(morse);
  printf("Voce inseriu a letra %c no texto\n", text[tamanho]);
  tamanho++;
}

extern void morse_bip();

int main() {

  // Initial Setup
  srand(time(NULL));
  long int k = 0;
  unsigned long int sw=0, bt=0;             // for reading switches and buttons
  unsigned long int test;
  long int i=0, j=0, l=0; // aux
  

  //threads
  int tid;

  //app specific
  

  int dev = open("/dev/de2i150_altera", O_RDWR);
  writeGreenLeds(0x0,dev);
  writeRedLeds(0x0,dev);
  //TODO - Create thread for decoding morse
  int maxt=0;

  #pragma omp parallel num_threads(3) private(tid)
  {
    tid = omp_get_thread_num();

    if(tid == 1) //thread responsavel por ler o caractere morse
    {
      while(1){
          count(dev);
      }
    }
    if(tid == 2){
     while(1){
        Intensity(tempo,dev);
      }
    }

    #pragma omp master
    {
      int prog = 1;
      while(prog)
      {
        bt = readButton(dev, &k);
        while(bt == BT1)
        {
          bt = readButton(dev, &k);
          tempo++;
        }
        while(bt == BT2)
        {
          bt = readButton(dev, &k);
          tempo2++;  
        }
        while(bt == BT3)
        {
          bt = readButton(dev, &k);
          tempo3++; 
        }
        if(tempo2 > 0)
        {
          tempo2=0;
          tamanho--;
          printf("Voce removeu a letra %c do texto\n", text[tamanho]);

        }
    
        if(tempo3 > 0)
        {
          tempo3=0;
          palavras++;

          text[tamanho] = '\0';
          printf("Nova palavra iniciada.\n");
          tamanho++;
          NumberToDisplay(palavras, dev);
        }

        if(bt == 0)
        {
          if(tempo > MAX_DOT_TIME) //traco
          {
            //morse_bip();
            morseCode[globalCounter] = '-';
            globalCounter++;
            if(globalCounter==1)
            {
              n8 = 64;
              writeDisplayRight(n5,n6,n7,n8, dev);
            }
            if(globalCounter==2)
            {
              n7 = n8;
              n8 = 64;
              writeDisplayRight(n5,n6,n7,n8, dev);
            }
            if(globalCounter==3)
            {
              n6 = n7;
              n7 = n8;
              n8 = 64;
              writeDisplayRight(n5,n6,n7,n8, dev); 
            }
            if(globalCounter==4)
            {
              n5 = n6;
              n6 = n7;
              n7 = n8;
              n8 = 64;
              writeDisplayRight(n5,n6,n7,n8, dev);
            }
            tempo = 0;
          }
          else if(tempo > 0 && tempo <= MAX_DOT_TIME)
          {
            morseCode[globalCounter] = '.';
            globalCounter++;
            if(globalCounter==1)
            {
              n8 = 63;
              writeDisplayRight(n5,n6,n7,n8, dev);
            }
            if(globalCounter==2)
            {
              n7 = n8;
              n8 = 63;
              writeDisplayRight(n5,n6,n7,n8, dev);
            }
            if(globalCounter==3)
            {
              n6 = n7;
              n7 = n8;
              n8 = 63;
              writeDisplayRight(n5,n6,n7,n8, dev); 
            }
            if(globalCounter==4)
            {
              n5 = n6;
              n6 = n7;
              n7 = n8;
              n8 = 63;
              writeDisplayRight(n5,n6,n7,n8, dev);
            }
            tempo = 0;
          }

        }
      }
    }
        

  }


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

