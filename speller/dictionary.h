// Declares a dictionary's functionality

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>
#include <cs50.h>
#include <stdio.h>
#include <ctype.h>

// Maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45

// Prototypes
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

node *hashtable[26];

//prototype of my hash function

bool check(const char *word);
bool load(const char *dictionary);
unsigned int size(void);
bool unload(void);

#endif // DICTIONARY_H
