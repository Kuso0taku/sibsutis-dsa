#include <stdlib.h>
#include <string.h>
#include "hashtab.h"

// pointer to current hash function (default KRHash)
static unsigned int (*current_hash)(char *) = KRHash;

void hashtab_set_hash(unsigned int (*hash_func)(char *)) {
    current_hash = hash_func;
}

unsigned int hashtab_hash(char *key) {
    return current_hash(key) % HASHTAB_SIZE;
}

void hashtab_init(listnode **hashtab) {
    for (int i = 0; i < HASHTAB_SIZE; i++) *(hashtab + i) = NULL;
}

void hashtab_add(listnode **hashtab, char *key, uint32_t value) {
    unsigned int idx = hashtab_hash(key);
    listnode *cur = *(hashtab + idx);
    // check if key exists
    while (cur) {
        if (strcmp(cur->key, key) == 0) {
            cur->value = value;
            return;
        }
        cur = cur->next;
    }
    // insert at head
    listnode *n = malloc(sizeof(listnode));
    n->key = strdup(key);
    n->value = value;
    n->next = *(hashtab + idx);
    *(hashtab + idx) = n;
}

listnode *hashtab_lookup(listnode **hashtab, char *key) {
    unsigned int idx = hashtab_hash(key);
    listnode *cur = *(hashtab + idx);
    while (cur) {
        if (strcmp(cur->key, key) == 0) return cur;
        cur = cur->next;
    }
    return NULL;
}

void hashtab_delete(listnode **hashtab, char *key) {
    unsigned int idx = hashtab_hash(key);
    listnode *cur = *(hashtab + idx);
    listnode *prev = NULL;
    while (cur) {
        if (strcmp(cur->key, key) == 0) {
            if (prev) prev->next = cur->next;
            else *(hashtab + idx) = cur->next;
            free(cur->key);
            free(cur);
            return;
        }
        prev = cur;
        cur = cur->next;
    }
}

// Kernighan–Ritchie hash
unsigned int KRHash(char *key) {
    unsigned int h = 0;
    while (*key) h = h * 31 + (unsigned char)*key++;
    return h;
}

// Jenkins hash
unsigned int JenkinsHash(char *key) {
    unsigned int hash = 0;
    while (*key) {
        hash += (unsigned char)*key++;
        hash += hash << 10;
        hash ^= hash >> 6;
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    return hash;
}
