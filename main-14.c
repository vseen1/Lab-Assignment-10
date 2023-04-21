#include <stdio.h>
#include <stdlib.h>

#define CHAR_SIZE 26

struct Trie {
    int isLeaf;
    struct Trie *character[CHAR_SIZE];
};

struct Trie* getNewTrieNode() {
    struct Trie* node = (struct Trie*) malloc(sizeof(struct Trie));
    node->isLeaf = 0;
    for (int i = 0; i < CHAR_SIZE; i++) {
        node->character[i] = NULL;
    }
    return node;
}

void insert(struct Trie **ppTrie, char *word) {
    struct Trie* curr = *ppTrie;
    while (*word) {
        if (curr->character[*word - 'a'] == NULL) {
            curr->character[*word - 'a'] = getNewTrieNode();
        }
        curr = curr->character[*word - 'a'];
        word++;
    }
    curr->isLeaf = 1;
}

int numberOfOccurrences(struct Trie *pTrie, char *word) {
    int res = 0;
    char *start = word; 
    while (*word) {
        pTrie = pTrie->character[*word - 'a'];
        if (pTrie == NULL) {
            return 0;
        }
        word++;
    }
    if (pTrie->isLeaf) {
        res++;
    }
    for (int i = 0; i < CHAR_SIZE; i++) {
        if (pTrie->character[i] != NULL) {
            res += numberOfOccurrences(pTrie->character[i], start); 
        }
    }
    return res;
}

struct Trie *deallocateTrie(struct Trie *pTrie) {
    if (pTrie == NULL) {
        return NULL;
    }
    for (int i = 0; i < CHAR_SIZE; i++) {
        deallocateTrie(pTrie->character[i]);
    }
    free(pTrie);
    return NULL;
}

int main(void) {
    struct Trie *trie = getNewTrieNode();
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i = 0; i < 5; i++) {
        insert(&trie, pWords[i]);
    }
    for (int i = 0; i < 5; i++) {
        printf("\t%s : %d\n", pWords[i], numberOfOccurrences(trie, pWords[i]));
    }
    trie = deallocateTrie(trie);
    if (trie != NULL) {
        printf("There is an error in this program\n");
    }
    return 0;
}

