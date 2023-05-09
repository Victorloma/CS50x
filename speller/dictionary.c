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
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26 * 27;

// Hash table
node *table[N];

// Create variable that tracks the word count
int word_count = 0;

// Create 2D array for storing and accessing hashes
int hash_arr[26][27];

// Set hash to 0 for first hash
int hash_val = 0;

// Create function that populates the 2D hash array with hash values
void populate_hash_arr()
{
    for (int i = 0; i < 26; i++)
    {
        for (int j = 0; j < 27; j++)
        {
            hash_arr[i][j] = hash_val++;
        }
    }
}

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Set index to hashed word
    int index = hash(word);

    // Create pointer that points to the index in the hash table, where the linked list starts
    node *ptr = table[index];

    // Loop through the linked list until the word is found or the list ends (in that case: pointer == NULL)
    while (ptr != NULL)
    {
        // Check word, return true if found
        if (strcasecmp(word, ptr->word) == 0)
        {
            return true;
        }
        // If not found, set pointer to next link in list
        ptr = ptr->next;
    }

    // If list didn't contain word, return false
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Improved hash function: searches for hash value in the hash array based on the first two letters of the word
    return hash_arr[toupper(word[0]) - 'A'][word[1] == '\0' ? 27 : (toupper(word[1]) - 'A')];
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Oper dictionary in read-only mode
    FILE *input = fopen(dictionary, "r");
    if (input == NULL)
    {
        // printf("Could not open %s.\n", *dictionary);
        return false;
    }
    if (input != NULL)
    {
        // Populate hash_arr with hash values
        populate_hash_arr();

        char buffer[LENGTH + 1];
        while (fscanf(input, "%s", buffer) != EOF)
        {
            // Allocate node for word
            node *n = malloc(sizeof(node));
            if (n == NULL)
            {
                printf("Not enough memory!\n");
                return 1;
            }
            strcpy(n->word, buffer);
            n->next = NULL;

            // Prepend node too list
            n->next = table[hash(buffer)];
            table[hash(buffer)] = n;

            // Increment word count
            word_count++;
        }
        fclose(input);
    }

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // Returns the amount of words loaded from input file
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Free memory in hash table
    for (int i = 0; i < N; i++)
    {
        node *ptr = table[i];
        while (ptr != NULL)
        {
            node *next = ptr->next;
            free(ptr);
            ptr = next;
        }
        if (i == N - 1)
        {
            return true;
        }
    }
    return false;
}
