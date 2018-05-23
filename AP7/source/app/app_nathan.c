#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#define SUBTRACT 0
#define SUM 1

/**
 * This application will sum or subtract two binary numbers and show the result in the 7-seg display in decimal.
 * Instructions:
 * From the 1st up to the 8th switch will be the first number A (8 bits)
 * From the 9th up to the 15th switch will be the second number B (7 bits)
 * The 16th switch (the third last switch) will be the sign switch: Up is sum and Down is subtraction.
 *  That is, if the sign switch is up the display will show A + B, else it will display A - B
 * That's it :) 
*/

unsigned char hexdigit[] = {0x3F, 0x06, 0x5B, 0x4F,
                            0x66, 0x6D, 0x7D, 0x07, 
                            0x7F, 0x6F, 0x77, 0x7C,
                            0x39, 0x5E, 0x79, 0x71,
                            0x40}; // 0x40 is represented as the negative sign in 

int main() {
  int i, j, k;
  int A, B, sign, result, neg;
  int digit[4] = { 0 };           // digits of the 7-seg display

  int dev = open("/dev/de2i150_altera", O_RDWR);  //"open" the altera board

  while(1) {                                // continuously read from the switches and write to the hex display
    read(dev, &j, 4);          // read from the switches

    if (j != -1) {
      printf("%d", j);  
    }
    
    A = j & 0xFF;                           // gets number A. (i.e. The state of the first 8 switches. 0xFF = 1111 1111'b )
    B = (j >> 8) & 0x7F;                    // gets number B. (i.e. Shifts 8 ignoring number A and gets the state of the next 7 switches 0x7F = 0111 1111'b)
    sign = (j & 0x8000) >> 15;                         // shifts 15 to get the state of the 16th switch. Same as doing: j & 0x7FFF

    switch(sign){
      case SUM:                             // if sign is 1, sum.
        result = A + B;
        break;
      case SUBTRACT:                        // if sign is 0, subtract;
        result = A - B;
        break;
      default:                              // else, signal that something went wrong.
        result = 0xFFFF;                    // since this number can never be reached
        break;
    }

    if(result < 0){                         // decide whether the result is negative and save this information in neg.
      result = -result;                     
      digit[3] = 16;                        // hexdigit[16] makes up the scheme for the negative sign in the 7-seg display
    } else {
      digit[3] = 0;
    }

    for (i = 0; i < 3; i++){                // put every decimal digit of result in a position of the array
      digit[i] = result % 10;               // (i.e. if result = 123 then digit[0] = 0, digit[1] = 1, digit[2] = 2...)
      result = result / 10;                 //
    }
    
    k =      hexdigit[ digit[0] ];         // "convert" decimal digit to a symbol in the first display
    k = k | (hexdigit[ digit[1] ]) <<  8;   // same as before and shift the number 8 times
    k = k | (hexdigit[ digit[2] ]) << 16;  // same as before and shift the number 16 times
    k = k | (hexdigit[ digit[3] ]) << 24;  // same as before and shift the number 24 times
                                               // this way every byte of k has a symbol for the display, which is how the driver will deal with it
                                    
    k = ~k;                                 // the display is active in low so... has to be negated.
    
    write(dev, &k, 4);                      // write four bytes in the hex display
  }

  close(dev);
  return 0;
}