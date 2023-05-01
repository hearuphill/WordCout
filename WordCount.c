#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILENAME_LENGTH 256
#define MAX_BUFFER_LENGTH 1024

enum
{
    CHAR_COUNT_MODE,
    WORD_COUNT_MODE
};

void show_help()
{
    printf("Usage: WordCount [-c | -w] [input_file_name]\n");
    printf("\t-c\tcount characters\n");
    printf("\t-w\tcount words\n");
}

int count_chars(FILE *fp)
{
    int c, count = 0;
    while ((c = fgetc(fp)) != EOF)
    {
        count++;
    }
    return count;
}

int count_words(FILE *fp)
{
    int c, count = 0;
    int in_word = 0;
    while ((c = fgetc(fp)) != EOF)
    {
        if (isalnum(c))
        {
            if (!in_word)
            {
                count++;
                in_word = 1;
            }
        }
        else
        {
            in_word = 0;
        }
    }
    return count;
}

int main(int argc, char *argv[])
{
    int mode = CHAR_COUNT_MODE;
    char filename[MAX_FILENAME_LENGTH];
    FILE *fp;

    // Parse command line arguments
    if (argc < 2)
    {
        show_help();
        return 0;
    }
    if (strcmp(argv[1], "-c") == 0)
    {
        mode = CHAR_COUNT_MODE;
    }
    else if (strcmp(argv[1], "-w") == 0)
    {
        mode = WORD_COUNT_MODE;
    }
    else
    {
        show_help();
        return 0;
    }
    if (argc < 3)
    {
        strncpy(filename, "input.txt", MAX_FILENAME_LENGTH);
    }
    else
    {
        strncpy(filename, argv[2], MAX_FILENAME_LENGTH);
    }

    // Open file
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Error: Can't open file '%s'!\n", filename);
        return 0;
    }

    // Count characters or words
    int count;
    if (mode == CHAR_COUNT_MODE)
    {
        count = count_chars(fp);
        printf("Character count: %d\n", count);
    }
    else if (mode == WORD_COUNT_MODE)
    {
        count = count_words(fp);
        printf("Word count: %d\n", count);
    }

    // Close file
    fclose(fp);

    return 0;
}
