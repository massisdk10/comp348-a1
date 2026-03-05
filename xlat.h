// This part tells compiler the functions that are defined in xlat.c, so that ftrans.c can call them, and also includes the necessary header files for the functions to work. 
#ifndef XLAT_H // Include guard to prevent multiple inclusions of this header file
#define XLAT_H

#include <stdio.h>

/* Caesar transformation */
void caesar_modif(FILE *in, int key);

/* XOR transformation */
void xor_modif(FILE *in, int key);

#endif