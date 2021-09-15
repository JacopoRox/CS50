#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <string.h>

int checkrepeat(string text);
int checklenght(string text);
int checkalpha(string text);
string keymod(string text);
string encoder(string code, string text);

int main(int argc, string argv[])
{
    if (argc != 2)  // Main first checks if the user gave a key
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    if (checklenght(argv[1]) != 0) // If the key is there it has to be of 26 characters
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    if (checkalpha(argv[1]) != 0) // Those characters must only be alphabetic
    {
        printf("Key must only contain alphabetic characters.\n");
        return 1;
    }
    if (checkrepeat(argv[1]) != 0) // and they must not be repeated
    {
        printf("Key must not contain repeated characters.\n");
        return 1;
    }

    string plaintext = get_string("plaintext: "); // If the key is valid the user is prompted for a plaintext

    printf("ciphertext: %s\n", encoder(keymod(argv[1]), plaintext)); // Which gets ciphered and printed

}

int checkrepeat(string text) // This function checks for reapeated characters in the key
{
    int len = strlen(text);
    int sum = 0;

    for (int i = 0; i < len; i++)
    {
        for (int j = 0; j < len; j++)
        {
            if (text[i] == text[j])
            {
                sum++;
            }
        }

    }
    if (sum == 26)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int checklenght(string text) // This function checks the lenght of the key
{
    int len = strlen(text);

    if (len != 26)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


int checkalpha(string text) // This function checks that the key contains only alphabetic characters
{
    int len = strlen(text);
    int sum = 0;

    for (int i = 0; i < len; i++)
    {
        if (text[i] >= 'A' && (text[i] <= 'Z'))
        {
            sum++;
        }
        else if (text[i] >= 'a' && (text[i] <= 'z'))
        {
            sum++;
        }
    }

    if (sum == 26)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
// This gets the plaintext and returns it after having changed all the alphabetic characters in it with the corresponding characters in the key
string encoder(string code, string text)
{
    int len = strlen(text);
    string abc = "abcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < len; i++) // This double loop check which letter of the alphabet each character in the plaintext is
    {
        for (int j = 0; j < 26; j++)
        {
            if (text[i] == abc[j])
            {
                text[i] = code[j]; // When it gets to the right letter it changes it with the corresponding in the key alphabet
                j = 26;
            }
            // If the letter is uppercase it is changed with its correspective uppercase in the key alphabet which has been previously lowercased
            else if (text[i] == abc[j] - 32)
            {
                text[i] = code[j] - 32;
                j = 26;
            }
        }
    }
    return text;
}

string keymod(string text) // This function changes all the characters in the key to lowercase and returns the modified key
{
    int len = strlen(text);
    for (int i = 0; i < len; i++)
    {
        if (text[i] >= 'A' && text[i] <= 'Z')
        {
            text[i] += 32;
        }
    }
    return text;
}
