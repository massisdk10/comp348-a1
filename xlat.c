//must include ceasar_modif and xor_modif functions, which are defined in xlat.c, so that ftrans.c can call them, and also include the necessary header files for the functions to work.
#include <stdio.h>
#include <ctype.h>
#include "xlat.h"

// helper function to shift a letter by a given key
static int shift_letter(int c, int key, int base) // helper function to shift a letter by a given key, the parameters are the character to be shifted and the key value, return the shifted character
{
    int offset = c - base; // calculate the offset of the character from the base (either 'A' or 'a')
    int k = key % 26; // calculate the effective key by taking the modulus with 26, since there are 26 letters in the alphabet
    int shifted = (offset + k) % 26; // calculate the shifted offset by adding the key and taking modulus with 26 to wrap around the alphabet
    if (shifted < 0) // if the shifted offset is negative, wrap around by adding 26
        shifted += 26;
    return base + shifted; // return the shifted character by adding the base back to the shifted
}

// helper function to shift a digit by a given key
static int shift_digit(int c, int key) // helper function to shift a digit
{
    int offset = c - '0'; // calculate the offset of the digit from '0'
    int k = key % 10; // calculate the effective key by taking the modulus with 10, since there are 10 digits
    int shifted = (offset + k) % 10; // calculate the shifted offset by adding the key and taking modulus with 10 to wrap around the digits
    if (shifted < 0) // if the shifted offset is negative, wrap around by adding 10
        shifted += 10;
    return '0' + shifted; // return the shifted digit by adding '0' back to the shifted
}

// implementation of the Caesar transformation
void caesar_modif(FILE *in, int key) 
{
    int c;
    while ((c = fgetc(in)) != EOF) // read each character from the input file until EOF
    {
        int out = c; // initialize the output character as the input character
        if (isupper(c)) // if the character is an uppercase letter, shift it using the helper function with base 'A'
            out = shift_letter(c, key, 'A');
        else if (islower(c)) // if the character is a lowercase letter, shift it using the helper function with base 'a'
            out = shift_letter(c, key, 'a');
        else if (isdigit(c)) // if the character is a digit, shift it using the helper function for digits
            out = shift_digit(c, key);
        putchar(out); // output the transformed character
    }
}

// implementation of the XOR transformation
void xor_modif(FILE *in, int key)
{   int c;
    while ((c = fgetc(in)) != EOF) // read each character from the input file until EOF
    {
        int out = c; // apply the XOR operation between the character and the key
        if (c >= 33 && c <= 126) // if the character is a printable ASCII character, apply the XOR transformation
        {
            int x = c ^ key; // XOR the character with the key
            if (x >= 33 && x <= 126) // if the result is a printable ASCII character, output it
            {
                out = x; // set the output character to the XOR result
            }
        }
        else // if the character is not a printable ASCII character, output it unchanged
        {
             out = c; // set the output character to the original character  
        }
        
        putchar(out); // output the transformed character
        
        
    }
} 