// Implements a dictionary's functionality

#include <stdbool.h>

//my libraries
#include <cs50.h>
//#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

int hashFunction(const char *vocab);
int countSize = 0;
bool boolSize;
// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int key = hashFunction(word);
    node *cursor = hashtable[key];
    while(cursor != NULL)
    {
        int inside = strcasecmp(word, cursor->word);
        cursor = cursor->next;
        if(inside == 0)
        {
            return true;
        }
    }
    return false;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    //direct the pointers in the array toward NULL
    for(int i = 0; i < 26; i++)
    {
        hashtable[i] = NULL;
    }
    FILE *readFile = fopen(dictionary, "r");
    if(readFile == NULL)
    {
        printf("out of memory");
        return false;
    }
    //load words in the dictionary into my data strucutre
    char word[50];
    while(fscanf(readFile, "%s", word) != EOF)
    {
        node *newNode = malloc(sizeof(node));
        if(newNode == NULL)
        {
            printf("out of memory");
            return false;
        }
        strcpy(newNode->word, word);
        newNode->next = NULL;
        char *vocab = newNode->word;
        int key = hashFunction(vocab);
        //let's put those words in linked lists!
        if(hashtable[key] == NULL)
        {
            hashtable[key] = newNode;
        }
        else
        {
            newNode->next = hashtable[key];
            hashtable[key] = newNode;
        }
        countSize++;
    }
    fclose(readFile);
    boolSize = true;
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    if(boolSize)
    {
        return countSize;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    for(int i = 0; i < 26; i++)
    {
        node *cursor = hashtable[i];
        while(cursor != NULL)
        {
            node *eraser = cursor;
            cursor = cursor->next;
            free(eraser);
        }
    }
    return true;
}

int hashFunction(const char *vocab)
{
    if(isupper(vocab[0]))
    {
        return vocab[0] - 65;
    }
    return vocab[0] - 97;
}
