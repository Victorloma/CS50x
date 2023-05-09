#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "wav.h"

bool check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    // TODO #1
    if (argc != 3)
    {
        printf("Usage: ./reverse input.wav output.wav\n");
        return 1;
    }

    // Open input file for reading
    // TODO #2
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 1;
    }

    // Read header
    // TODO #3
    WAVHEADER header;
    fread(&header, sizeof(WAVHEADER), 1, input);

    // Use check_format to ensure WAV format
    // TODO #4
    check_format(header);
    if (!check_format(header))
    {
        printf("Input is not a WAV file.\n");
        return 1;
    }

    // Open output file for writing
    // TODO #5
    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        fclose(input);
        printf("Could not create %s. \n", argv[2]);
        return 1;
    }

    // Write header to file
    // TODO #6
    fwrite(&header, sizeof(WAVHEADER), 1, output);

    // Use get_block_size to calculate size of block
    // TODO #7
    int block_size = get_block_size(header);

    // Write reversed audio to file
    // TODO #8

    // Make buffer to store the the current audio block and allocate memory to it.
    BYTE *audio_block = malloc(block_size);

    // Set starting pointer at the end of the input file.
    fseek(input, -block_size, SEEK_END);
    // While the pointer value is equal or higher than the header size, execute the loop.
    while (ftell(input) >= sizeof(header))
    {
        // Read audio block and store to buffer.
        fread(&audio_block, block_size, 1, input);
        // Copy audio block from buffer and store to output file.
        fwrite(&audio_block, block_size, 1, output);
        // If we cannot move the pointer back two block return 1 to stop the loop.
        if (fseek(input, 2 * -block_size, SEEK_CUR))
        {
            return 1;
        }
    }

    fclose(output);
    fclose(input);
}

bool check_format(WAVHEADER header)
{
    // TODO #4
    char *WAV = "WAVE";
    bool format_ok = true;

    for (int i = 0, n = 4; i < n; i++)
    {
        if (header.format[i] != WAV[i])
        {
            format_ok = false;
        }
    }

    return format_ok;
}

int get_block_size(WAVHEADER header)
{
    // TODO #7
    int block_size = header.numChannels * header.bitsPerSample / 8;
    return block_size;
}