#include <cs50.h>
#include <stdio.h>

// This function takes an integer as an argument and print out that number of #
void block(int i)
{
    for (int x = 0; x < i; x++)
    {
        printf("#");
    }
    
}

// This function takes an integer as an argument and print out that number of spaces
void space(int i)
{
    for (int x = 0; x < i; x++)
    {
        printf(" ");
    }
    
}

int main(void)
{
    int n;
    do
    {
        n = get_int("Size: ");
    }
    while ((n < 1) | (n > 8));

    // b is a variable that needs to be equal to n which can't change during the running of the program
    int b = n;

    // This part of the program print out the correct ammount of # and spaces for each line in order to build the piramid
    for (int j = 1; j <= n; j++)
        {
            space(b - 1);
            block(j);   // The variable j start as 1 and gets +1 every time this part of the program is run in order to print the right ammount of # for each line
            printf("  ");
            block(j);
            space(b - 1);
            printf("\n");
            b--;
            
        }
}