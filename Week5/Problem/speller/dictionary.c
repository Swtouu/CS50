#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Choose a reasonable number of buckets in the hash table
const unsigned int N = 65536; // A power of 2 can be efficient

// Hash table
node *table[N];

// Dictionary size
unsigned int dict_size = 0;

// Hashes word to a number
unsigned int hash(const char *word)
{
    // A better hash function (djb2) for strings
    unsigned int hash_value = 5381;
    int c;

    while ((c = *word++))
    {
        hash_value = ((hash_value << 5) + hash_value) + c; // hash * 33 + c
    }

    return hash_value % N;
}

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    char lowercase_word[LENGTH + 1];
    strcpy(lowercase_word, word);

    // Convert the word to lowercase
    for (int i = 0; lowercase_word[i] != '\0'; i++)
    {
        lowercase_word[i] = tolower(lowercase_word[i]);
    }

    // Retrieve the hash value
    unsigned int index = hash(lowercase_word);

    // Search the string in the dictionary
    for (node *tmp = table[index]; tmp != NULL; tmp = tmp->next)
    {
        if (strcmp(lowercase_word, tmp->word) == 0)
        {
            return true;
        }
    }

    return false;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open Dictionary File
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    // Read Strings from File
    char buffer[LENGTH + 1];
    while (fscanf(file, "%s", buffer) != EOF)
    {
        // Create a New Node
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            fclose(file);
            return false;
        }
        strcpy(n->word, buffer);
        n->next = NULL;

        // Hash Word
        unsigned int index = hash(buffer);

        // Insert Node into Hash Table
        n->next = table[index];
        table[index] = n;

        // Increment the word counter
        dict_size++;
    }

    // Close Dictionary File
    fclose(file);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return dict_size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (unsigned int i = 0; i < N; i++)
    {
        node *current = table[i];
        while (current != NULL)
        {
            node *next = current->next;
            free(current);
            current = next;
        }
        table[i] = NULL;
    }

    return true;
}
