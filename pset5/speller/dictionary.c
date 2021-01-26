// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

int dsize = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // cursor points to the correct table
    node *cursor = table[hash(word)];
    while (cursor != NULL) // iterates untill the end of the linked list
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true; // returns true if it finds the word
        }
        else
        {
            cursor = cursor->next; // keeps going if it doesn't
        }
    }
    return false; // return false if the word is not there
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // iterates through the word and hashes it to the table corresponding to the first letter it finds
    for (int i = 0; i < strlen(word); i ++)
    {
        if (tolower(word[i]) >= 97 && tolower(word[i]) <= 122)
        {
            return tolower(word[0]) - 97;
        }
    }
    return 0; // return 0 if the word has no letters
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *dfile = fopen(dictionary, "r"); // opens the file to read
    if (dfile == NULL)
    {
        return false;
    }
    char *buffer = malloc(LENGTH + 1); // allocates enough memory for the longest possible word
    node *n = NULL;

    for (int i = 0; i < N; i++) // sets all table to point to NULL
    {
        table[i] = NULL;
    }

    while (fscanf(dfile, "%s", buffer) != EOF) // iterates through the file
    {
        n = malloc(sizeof(node)); // new node
        if (n == NULL) // check if there is enough space
        {
            return false;
        }
        strcpy(n->word, buffer); // copies the word from the buffer to the new node
        n->next = table[hash(n->word)]; // points the node to the first node of the hashed table
        table[hash(n->word)] = n; // set the table to point to the new first node
        dsize++; // keeps track of the words in the dictionary
    }
    free(buffer);
    fclose(dfile);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return dsize;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    node *cursor = NULL;
    node *tmp = NULL;
    for (int i = 0; i < N; i++) // iterates though all the tables
    {
        cursor = table[i];
        while (cursor != NULL) // iterates through the linked list and frees all nodes
        {
            tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;
}
