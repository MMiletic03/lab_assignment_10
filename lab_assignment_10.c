#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Trie
{
    int flag;
    struct Trie* children[26];

}Trie;

void insert(struct Trie **ppTrie, char *word)
{
    // if the trie is empty
    if (*ppTrie == NULL) 
    {
        return;
    }

    //initalize temp variable
    Trie *temp = *ppTrie;
    int length = strlen(word);
    for (int i = 0; i < length; i++) 
    {
        int index = word[i] - 'a';
        if (temp->children[index] == NULL) 
        {
            // allocate memory for that child
            temp->children[index] = calloc(1, sizeof(Trie));
        }
        temp = temp->children[index];
    }
    temp->flag++;
}


int numberOfOccurances(struct Trie *pTrie, char *word)
{
    //if the trie is empty
    if (pTrie == NULL) 
    {
        return 0;
    }

    //initalize temp variable
    Trie *temp = pTrie;
    int length = strlen(word);
    for (int i = 0; i < length; i++) 
    {
        int index = word[i] - 'a';
        if (temp->children[index] == NULL) 
        {
            //once the temp pointer has made it to the end of the word, it appends the flag variable
            return 0;
        }
        temp = temp->children[index];
    }
    return temp->flag;
}


struct Trie *deallocateTrie(struct Trie *pTrie)
{

    for(int i = 0; i<26; i++)
    {
        if(pTrie->children[i] != NULL)
        {
            deallocateTrie(pTrie->children[i]);
        }
    }
    free(pTrie);
    return NULL;
}



int main(void)
{

    //initalize root of the Trie structure using calloc to initalize all the children to NULL
    Trie *trie = calloc(1,sizeof(Trie));
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    //pass each of the words into the insert function to allocate nodes for each letter to form each word
    for(int i = 0; i < 5; i++)
    {
        insert(&trie,pWords[i]);
    }
    //print the words in the trie, and their number of occurances
    for(int i = 0; i < 5; i++)
    {
        printf("\t%s : %d\n", pWords[i], numberOfOccurances(trie, pWords[i]));
    }

    //frees the memory inside of the trie
    trie = deallocateTrie(trie);
    //checks if the trie has been fully deallocated
    if(trie != NULL)
    {
        printf("there is an error in this program\n");
    }
    return 0;
}