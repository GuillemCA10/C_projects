// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 10007;

unsigned int wordcount; // Stores the number of words in the dictionary
bool loaded = false;    // Registers whether load() returned true or not.

// Hash table
node *table[N] = {NULL};

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    node *lookup = table[hash(word)];

    while (lookup != NULL)
    {
        if (strcasecmp(lookup->word, word) == 0)
            return true;

        lookup = lookup->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function

    unsigned int h = 0;

    for (int i = 0; word[i] != '\0'; i++)
    {
        h = h * 31 + tolower(word[i]);
    }

    return h % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // Open dictionary file
    FILE *source = fopen(dictionary, "r");
    if (source == NULL)
    {
        printf("Could not open file \n");
        return false;
    }

    // Read each word in the file
    char *buffer = malloc(LENGTH + 1);
    if (buffer == NULL)
    {
        fclose(source);
        return false;
    }

    while (fscanf(source, "%s", buffer) == 1)
    {
        wordcount++;
        // Add each word to the hash table. Match first word to index number with hash function.
        int index = hash(buffer);

        // allocate memory for a new node and create a pointer that stores the address,
        node *entry = malloc(sizeof(node));
        if (entry == NULL)
        {
            fclose(source);
            free(buffer);
            return false;
        }
        // copy word stored in buffer to the .word field in that address
        strcpy(entry->word, buffer);
        entry->next = table[index];
        // now point table[index] to new node
        table[index] = entry;
    }

    // Close the dictionary file
    fclose(source);
    free(buffer);
    loaded = true;
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    if (loaded)
        return wordcount;

    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];

        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;
}
