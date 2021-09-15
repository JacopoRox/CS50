#include <cs50.h>
#include <stdio.h>

void thirteen(long number);
void fifteen(long number);
void sixteen(long number);

int main(void) //This part of the function prompt the user to insert a credit card number that has to be more than 0
{   
    long number;
    do
    {
        number = get_long("Number: ");
    }
    while (number < 0);

    if (number > 999999999999 && number < 10000000000000) // If the number has thirteen digits it runs the thirteen fuction
    {
        thirteen(number);
    }
    else if (number > 99999999999999 && number < 1000000000000000) // If the number has fifteen digits it runs the fifteen fuction
    {
        fifteen(number);
    }
    else if (number > 999999999999999 && number < 10000000000000000) // If the number has sixteen digits it runs the sixteen fuction
    {
        sixteen(number);
    }
    else    // Any other number will result as invalid
    {
        printf("INVALID\n");
    }   
}
void thirteen(long number) // This function check if the thirteen digits number is a valid one and print VISA if it is 
{
    int digits = 0; // These variables will start as 0s and will be growing as we sum up digits
    int others = 0;
 
    for (long x = 100; x < 10000000000000; x = x * 100)
    {   
        // Every other digits is multiplied by two and than the two digits of the new number are added to the others variable
        int a = ((number % x) / (x / 10)) * 2;
        int a1 = a % 10;
        int a2 = (a % 100) / 10;
        others = others + a1 + a2;
    }

    for (long x = 10; x < 100000000000000; x = x * 100)
    {   
        // Digits not previusly multiplide by two are now summed up in the variable digits
        int b = ((number % x) / (x / 10));
        digits = digits + b;
    }

    int checksum = digits + others; 

    int check = checksum % 10; // Checksum last digits needs to be 0 for the card to be VALID
    if (check == 0 && (number % 10000000000000) / 1000000000000 == 4) 
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }    
}
void fifteen(long number) // This function check if the 15 digits number is a valid one and print AMEX if it is 
{
    int digits = 0;
    int others = 0;

    for (long x = 100; x < 1000000000000000; x = x * 100) // This part is the same as before but operates on 15 digits
    {
        int a = ((number % x) / (x / 10)) * 2;
        int a1 = a % 10;
        int a2 = (a % 100) / 10;
        others = others + a1 + a2;
    }

    for (long x = 10; x < 10000000000000000; x = x * 100)
    {
        int b = ((number % x) / (x / 10));
        digits = digits + b;
    }

    int checksum = digits + others;

    int check = checksum % 10;
    if (check == 0) 
    {
        if ((number % 1000000000000000) / 10000000000000 == 34 || (number % 1000000000000000) / 10000000000000 == 37)
        {
            printf("AMEX\n");
        }
        else 
        {
            printf("INVALID\n");
        }
    }
    else 
    {
        printf("INVALID\n");
    }    
}
void sixteen(long number) 
// This function check if the 16 digits number is a valid one and print VISA if it starts with 4 or MASTERCARD if it starts with 51, 52, 53, 54 or 55
{
    int digits = 0;
    int others = 0;

    for (long x = 100; x < 100000000000000000; x = x * 100) // This part is the same as before but operates on 16 digits
    {
        int a = ((number % x) / (x / 10)) * 2;
        int a1 = a % 10;
        int a2 = (a % 100) / 10;
        others = others + a1 + a2;
    }

    for (long x = 10; x < 10000000000000000; x = x * 100)
    {
        int b = ((number % x) / (x / 10));
        digits = digits + b;
    }

    int checksum = digits + others;

    int check = checksum % 10;
    if (check == 0) 
    {
        if ((number % 10000000000000000) / 1000000000000000 == 4)
        {
            printf("VISA\n");
        }
        else if ((number % 10000000000000000) / 100000000000000 > 50 && (number % 10000000000000000) / 100000000000000 < 56)
        {
            printf("MASTERCARD\n");
        }
        else 
        {
            printf("INVALID\n");
        }
    }
    else 
    {
        printf("INVALID\n");
    }    
}
