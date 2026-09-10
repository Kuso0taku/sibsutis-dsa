#ifndef HASHTAB_H
#define HASHTAB_H
#include <stdint.h>

#define HASHTAB_SIZE 20000   // number of buckets

// linked list node for chaining
typedef struct listnode {
    char *key;
    uint32_t value;
    struct listnode *next;
} listnode;

// default hash function (calls current hash)
unsigned int hashtab_hash(char *key);

// set the hash function used by hashtab_hash
void hashtab_set_hash(unsigned int (*hash_func)(char *));

// initialize all buckets to NULL
void hashtab_init(listnode **hashtab);

// add key-value pair (update if key exists)
void hashtab_add(listnode **hashtab, char *key, uint32_t value);

// lookup key, returns node or NULL
listnode *hashtab_lookup(listnode **hashtab, char *key);

// delete node by key, freeing memory
void hashtab_delete(listnode **hashtab, char *key);

// Kernighan–Ritchie hash (BKDR)
unsigned int KRHash(char *key);

// Jenkins one-at-a-time hash
unsigned int JenkinsHash(char *key);

#endif
