// Implements a dictionary's functionality

#include <stdbool.h>
//my header files
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#include "dictionary.h"

//make my root pointer
node *root = NULL;
int wordInDictionary = 0;

//void freeTrie(node *firstNode);

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    node *cursor = root;
    int key = 0;
    for(int i = 0, n = strlen(word); i < n; i++)
    {
        if(word[i] == '\'')
        {
            key = 26;
        }
        else
        {
            key = tolower(word[i]) - 97;
        }
        if(cursor->children[key] == NULL)
        {
            return false;
        }
        else
        {
            cursor = cursor->children[key];
        }
    }
    return cursor->isWord;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    root = malloc(sizeof(node));
    for(int i = 0; i < 27; i++)
    {
        root->children[i] = NULL;
    }
    FILE *readFile = fopen(dictionary, "r");
    if(readFile == NULL)
    {
        printf("out of memory\n");
        return false;
    }
    char word[LENGTH + 1];
    while(fscanf(readFile, "%s", word) != EOF)
    {
        node *cursor = root;
        int key = 0;
        //interate throught the word
        for(int i = 0, n = strlen(word); i < n; i++)
        {
            if(word[i] == '\'')
            {
                key = 26;
            }
            else
            {
                key = word[i] - 97;
            }
            if(cursor->children[key] == NULL)
            {
                node* newNode = malloc(sizeof(node));
                for(int j = 0; j < 27; j++)
                {
                    newNode->children[j] = NULL;
                }
                if(newNode == NULL)
                {
                    printf("out of memeory\n");
                    return false;
                }
                cursor->children[key] = newNode;
                cursor = newNode;
            }
            else
            {
                cursor = cursor->children[key];
            }
        }
        //insert "true" at the end of the word!
        cursor->isWord = true;
        wordInDictionary++;
        fclose(readFile);
    }
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return wordInDictionary;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    //node *firstNode = root;
    //freeTrie(firstNode);
    return true;
}

void freeTrie(node *firstNode)
{

    if(firstNode == NULL)
    {
        return;
    }
    for(int i = 0; i < 27; i++)
    {
        freeTrie(firstNode->children[i]);
    }
    free(firstNode);
}
