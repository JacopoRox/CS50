#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

float letterscount(string s);
float wordscount(string s);
float sentencescount(string s);

int main(void)
{
    string text = get_string("Text: "); // Prompt the user for a text and store the answer in a string

    double L = (letterscount(text) * 100 / wordscount(text)); // Calculate the number of letters per 100 words
    double S = (sentencescount(text) * 100 / wordscount(text)); // Calculate the number of sentences per 100 words
    double index = 0.0588 * L - 0.296 * S - 15.8; // Calculate the Coleman-Liau index

    int grade = round(index); // Round the index to the nearest integer

    if (grade <= 16 && grade > 0) // Print out the previously optained Grade
    {
        printf("Grade %i\n", grade);
    }

    else if (grade < 1)
    {
        printf("Before Grade 1\n");
    }

    else if (grade > 16)
    {
        printf("Grade 16+\n");
    }
}

// This function take a string as an argument and counts the all the letters in that string
float letterscount(string s)
{
    float letters = 0;
    int n = strlen(s);
    for (int i = 0; i < n; i++)
    {
        if (s[i] >= 'a' && s[i] <= 'z')
        {
            letters++;
        }
        else if (s[i] >= 'A' && s[i] <= 'Z')
        {
            letters++;
        }
    }
    return letters;
}

// This function take a string as an argument and counts the all the words in that string
float wordscount(string s)
{
    float words = 1;
    int n = strlen(s);
    for (int i = 0; i < n; i++)
    {
        if (s[i] == ' ')
        {
            words++;
        }
    }

    return words;
}

// This function take a string as an argument and counts the number of characters that end a sentence (. / ? / !)
float sentencescount(string s)
{
    float sentences = 0;
    int n = strlen(s);
    for (int i = 0; i < n; i++)
    {
        if (s[i] == '.' || s[i] == '!' || s[i] == '?')
        {
            sentences++;
        }
    }
    return sentences;
}