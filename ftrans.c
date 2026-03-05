// controling part
// 1. read command line, 
// 2.validate input and open the file
// 3. call the function to do the work
// 4. handling errors 

//program runs by command line: ./ftrans <mode> <parameter> <input_file>
// using argv[] with 0: program name, 1: mode, 2: parameter, 3: input file

//Modes: caesar,xor, dict
// Open file before calling the function 

//ERROR 1: if the number of arguments is not 4, print usage message and exit 
//ERROR 2: if the mode is not valid, print error message and exit
//ERROR 3: if the parameter is not valid for the mode, print error message
//ERROR 4: if the file cannot be opened, print error message and exit

//1) ftrans.c must know how to call the functions in ftrans.h, so include the header files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "xlat.h"
#include "dict.h"
#include <limits.h>

#define ERROR_INVALID_ARGUMENTS 1
#define ERROR_INVALID_MODE 2
#define ERROR_INVALID_PARAMETER 3
#define ERROR_FILE_OPEN 4

//helpers

static void print_usage(const char *prog) // print usage message, the parameter is the program name, which is argv[0]
{
    fprintf(stderr, "Usage: %s <mode> <parameter> <input_file>\n", prog);
    fprintf(stderr, "Modes: caesar | xor | dict\n");
}

static void to_lower_str(char *s) // convert a string to lowercase, the parameter is the string to be converted
{
    while (*s)
    {
        *s = tolower(*s);
        s++;
    }
}

static int parse_int_strict(const char *s, int *out) // parse a string to an integer, the parameters are the string to be parsed and a pointer to store the result, return 1 if successful, 0 otherwise
{
    char *end;
    long val = strtol(s, &end, 10); // parse the string to a long integer, the base is 10

    if (*end != '\0')// if there are extra characters after the number, return 0 making sure the string is a valid integer
        return 0;

    *out = (int)val;
    return 1;
}

//start of the main 

int main(int argc, char *argv[])
{
    if (argc != 4) // check if the number of arguments is 4, if not, error
    {
        print_usage(argv[0]); // from helper function, print usage message
        return ERROR_INVALID_ARGUMENTS;
    }

    // read command line arguments, and store them in variables for easier use
    const char *mode_input = argv[1];
    const char *parameter_input = argv[2];
    const char *input_file = argv[3]; 

    char mode[15]; // create a buffer to store the lowercase mode
    snprintf(mode, sizeof(mode), "%s", mode_input); 
    to_lower_str(mode);

    FILE *file = fopen(input_file, "r"); // open the input file for reading
    if (file == NULL) // if the file cannot be opened, error
    {
        fprintf(stderr, "Error: Unable to open file %s\n", input_file);
        return ERROR_FILE_OPEN;
    }

    //switch case for the mode, call the corresponding function based on the mode
    if (strcmp(mode, "caesar") == 0) // if the mode is caesar, call the caesar function
    {
        int shift;
        if (!parse_int_strict(parameter_input, &shift) || shift == 0) // parse the parameter to an integer, if it fails or if the shift is 0, error
    {
        fprintf(stderr, "Error: Caesar key must be a non-zero integer.\n");
        fclose(file);
        return ERROR_INVALID_PARAMETER;
    }
    caesar_modif(file, shift); // call the caesar function with the file and the shift value
    }
    else if (strcmp(mode, "xor") == 0) // if the mode is xor, call the xor function
    {
        int key;
        if (!parse_int_strict(parameter_input, &key)) // parse the parameter to an integer, if it fails, error
        {
            fprintf(stderr, "Error: Invalid parameter for xor mode. Expected an integer.\n");
            fclose(file);
            return ERROR_INVALID_PARAMETER;
        }
        xor_modif(file, key); // call the xor function with the file and the key value
    }
    else if (strcmp(mode, "dict") == 0) // if the mode is dict, call the dict function
    {
        dict_modif(file); // call the dict function with the file
    }
    else // if the mode is not valid, error
    {
        fprintf(stderr, "Error: Invalid mode '%s'. Valid modes are: caesar | xor | dict\n", mode_input);
        fclose(file);
        return ERROR_INVALID_MODE;
    }

    fclose(file); // close the file after processing
    return 0;

}

