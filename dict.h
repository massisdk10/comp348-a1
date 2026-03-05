// This part tells compiler the functions that are defined in dict.c, so that ftrans.c can call them, and also includes the necessary header files for the functions to work.

#ifndef DICT_H
#define DICT_H

#include <stdio.h>

void dict_modif(FILE *in);

#endif