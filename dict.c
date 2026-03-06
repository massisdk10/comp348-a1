

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>   
#include <ctype.h>

#define MAX_DICT 20           // Maximum number of dictionary entries
#define MAX_WORD 128           // Maximum length of a single word

static char *src[MAX_DICT];
static char *dst[MAX_DICT];
static int dict_size = 0;

/* remove leading and trailing spaces */
static char *trim(char *s)
{
    while (isspace(*s)) s++;

    char *end = s + strlen(s) - 1;
    while (end > s && isspace(*end))
    {
        *end = '\0';
        end--;
    }

    return s;
}

/* load dictionary file */
static void load_dictionary(const char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (!fp)                               // If file could not be opened print error and exit
    {
        fprintf(stderr, "Error: cannot open dictionary file\n");
        exit(1);
    }

    char line[256];

    while (fgets(line, sizeof(line), fp) && dict_size < MAX_DICT)      // Read each line until EOF or max entries
    {
        char *eq = strchr(line, '=');
        if (!eq) continue;

        *eq = '\0';

        char *left = trim(line);             // Trim leading/trailing spaces from source word
        char *right = trim(eq + 1);         // Trim leading/trailing spaces from destination word

        right[strcspn(right, "\n")] = '\0';

        src[dict_size] = strdup(left);
        dst[dict_size] = strdup(right);

        dict_size++;
    }

    fclose(fp);
}

/* find translation */
static const char *lookup(const char *word)
{
    for (int i = 0; i < dict_size; i++)
    {
        if (strcasecmp(word, src[i]) == 0)
            return dst[i];
    }
    return NULL;
}

/* apply capitalization style */
static void print_with_case(const char *original, const char *replacement)
{
    int len = strlen(original);

    int all_upper = 1;
    int all_lower = 1;

    for (int i = 0; i < len; i++)
    {
        if (!isupper(original[i])) all_upper = 0;
        if (!islower(original[i])) all_lower = 0;
    }

    if (all_upper)
    {
        for (int i = 0; replacement[i]; i++)
            putchar(toupper(replacement[i]));
    }
    else if (all_lower)
    {
        printf("%s", replacement);
    }
    else if (isupper(original[0]))
    {
        putchar(toupper(replacement[0]));
        printf("%s", replacement + 1);
    }
    else
    {
        printf("%s", replacement);
    }
}

/* main dictionary transformation */
void dict_modif(FILE *in)
{
    char dictfile[256];

    printf("Enter dictionary file: ");
    scanf("%255s", dictfile);          // Read dictionary filename

    load_dictionary(dictfile);         // Load dictionary into memory

    char word[MAX_WORD];
    int i = 0;
    int c;

    while ((c = fgetc(in)) != EOF)     // Read input file character by character
    {
        if (isalpha(c))                // If character is a letter  
        {
            word[i++] = c;
        }
        else      // If Non-letter character
        {
            if (i > 0)
            {
                word[i] = '\0';

                const char *rep = lookup(word);        // Look for replacement in dictionary

                if (rep)
                    print_with_case(word, rep);      // Print replacement with correct case
                else
                    printf("%s", word);              // Print original word if not in dictionary

                i = 0;
            }

            putchar(c);
        }
    }

    if (i > 0)        //if file ends while a word is still in buffer
    {
        word[i] = '\0';
        const char *rep = lookup(word);  // Look for replacement in dictionary

        if (rep)
            print_with_case(word, rep);
        else
            printf("%s", word);
    }
}