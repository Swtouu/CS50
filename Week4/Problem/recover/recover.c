#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t BYTE;

const int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover IMAGE\n");
        return 1;
    }

    char *inputName = argv[1];
    FILE *input = fopen(inputName, "r");
    if (input == NULL)
    {
        fprintf(stderr, "Could not open the file %s.\n", inputName);
        return 1;
    }

    BYTE block[BLOCK_SIZE];
    bool probablyJPEG = false;
    int outputNumber = 0;
    FILE *output = NULL;

    while (fread(block, 1, BLOCK_SIZE, input) == BLOCK_SIZE)
    {
        if (block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff && (block[3] & 0xf0) == 0xe0)
        {
            if (output != NULL)
            {
                fclose(output);
            }

            char outputName[8];
            sprintf(outputName, "%03i.jpg", outputNumber);

            output = fopen(outputName, "w");
            if (output == NULL)
            {
                fprintf(stderr, "Could not create the file %s.\n", outputName);
                return 1;
            }
            outputNumber++;
            probablyJPEG = true;
        }

        if (probablyJPEG)
        {
            fwrite(block, 1, BLOCK_SIZE, output);
        }
    }

    if (output != NULL)
    {
        fclose(output);
    }

    fclose(input);
    return 0;
}
