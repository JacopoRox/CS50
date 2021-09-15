#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Checks if the program is run correctly
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
    // Open the memory card
    FILE *file = fopen(argv[1], "r");

    // and checks if it was opened correctly
    if (file == NULL)
    {
        printf("Memory card not opened successfully\n");
        return 1;
    }

    unsigned char bytes[512]; // Generates a buffer to store data

    int f = 0; // var to keep track of the founded jpg image
    char *name = malloc(9); // allocate space for a string that is going to contain our image name
    sprintf(name, "%03i.jpg", f); // print the first name to the allocated space
    FILE *jpg = NULL; // this pointer is going to point to images

    // repeat until the end of the image (fread returns 0)
    while (fread(bytes, 512, 1, file))
    {
        // if it is the beginning of jpg file
        if (bytes[0] == 0xff && bytes[1] == 0xd8 && bytes[2] == 0xff && (bytes[3] & 0xf0) == 0xe0)
        {
            // if it is the first jpg file opens a file and set the jpg pointer to it
            if (f == 0)
            {
                jpg = fopen(name, "w");
                fwrite(bytes, 512, 1, jpg); // start writing the first block to the file
                f++; // updates the number of found jpg
            }
            else // if it is not the first
            {
                fclose(jpg); // close whatever jpg is pointing at
                sprintf(name, "%03i.jpg", f); // updates the name of the file
                jpg = fopen(name, "w"); // and generates a new file with that name
                fwrite(bytes, 512, 1, jpg); // starts writing to it
                f++; // updates the counter
            }
        }
        // if a jpg was already found keeps writing to it
        else if (f > 0)
        {
            fwrite(bytes, 512, 1, jpg);
        }
    }
    // close everything and frees memory
    fclose(jpg);
    fclose(file);
    free(name);
    return 0;
}

