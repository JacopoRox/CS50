#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>

int main(void)
{
    int numbers[] = {6, 5, 3, 8, 1, 2, 9, 4, 7};

    for (int counter = 1; counter != 0;)
    {
        counter = 0;
        for (int i = 0; numbers[i + 1] != '\0'; i++)
        {
            if (numbers[i] > numbers[i + 1])
            {
                int temp = numbers[i];
                numbers[i] = numbers[i + 1];
                numbers[i + 1] = temp;
                counter++;
            }

        }
    }
    for (int i = 0; numbers[i] != '\0'; i++)
    {
        printf("%i, ", numbers[i]);
    }
}