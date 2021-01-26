#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>

int main(void)
{
    int numbers[9] = {6, 5, 3, 8, 1, 2, 9, 4, 7};

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (numbers[i] > numbers[j])
            {
                int temp = numbers[i];
                numbers[i] = numbers[j];
                numbers[j] = temp;
            }
        }
    }


    for (int i = 0; i < 9; i++)
    {
        printf("%i ", numbers[i]);
    }
    printf("\n");
}
for (int i = 0; i < candidate_count; i++)
{
    for (int j = 0; i < candidate_count; j++)
    {
        if (lock[i][j] == TRUE)
        {
            int check++
        }
    }
if (pairs[i].winner != )
}