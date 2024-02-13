#ifndef MY_PROJECT_TRIE__
#define MY_PROJECT_TRIE__

#include <stddef.h> /* size_t */

typedef struct trie_node trie_node_t;
typedef struct trie_tree trie_t;

trie_t *TrieCreate(void);

void TrieDestroy(trie_t *trie);

int TrieInsert(const trie_t *trie, unsigned int requested_num, unsigned int *result, size_t n);

int Search(const trie_t *trie, unsigned int requested_num, size_t n);

int TrieSearchAndInsert(const trie_t *trie, unsigned int requested_num, unsigned int *result, size_t n);

int TrieIsEmpty(const trie_t *trie);

int TrieIsFULL(const trie_t *trie);

int TrieFree(const trie_t *trie, unsigned int num_to_free, size_t n);

size_t TrieCount(const trie_t *trie);

#endif
