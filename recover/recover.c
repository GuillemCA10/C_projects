#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
 
const size_t BYTES = 512;
 
int main(int argc, char *argv[])
{
    // Check for correct usage
    if (argc != 2)
    {
        printf("Usage: recover [file]\n");
        return 1;
    }
 
    // Open memory card
 
    FILE *input = fopen(argv[1], "rb");
 
    // Declare a pointer to an address in which to output a photo
 
    FILE *output = NULL;
 
    // Check for opening error
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }
 
    // Create a buffer to store card data
    uint8_t buffer[BYTES];
 
    // Create a buffer to store file names
    char filename[16];
 
    int imgcount = 0;
 
    // While there's still data left to read
    while (fread(buffer, 1, BYTES, input) == BYTES)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            if (output != NULL)
            {
                fclose(output);
                output = NULL;
                imgcount++;
            }
 
            snprintf(filename, sizeof(filename), "%03i.jpg", imgcount);
 
            output = fopen(filename, "wb");
            fwrite(buffer, 1, BYTES, output);
        }
 
        else if (output != NULL)
        {
            fwrite(buffer, 1, BYTES, output);
        }
    }
 
    fclose(input);
 
    if (output != NULL)
    {
        fclose(output);
    }
}
