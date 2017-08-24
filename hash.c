// hash.c

#include <string.h>
#include <math.h>

#include "debug.h"

#define HT_PRIME_A 3626149
#define HT_PRIME_B 3021377

// computes a hash of a string
int ht_hash(const char* s, const int prime, const int m) {
    debug(("ht_hash(%s, %d, %d)", s, prime, m));
    const int len = strlen(s);
    long hash = 0;
    for (int i = 0; i < len; i++) {
        hash += (long)pow(prime, len - (i + 1)) * s[i];
        hash = hash % m;
    }
    return (int)hash;
}

// computes a hash of a string and is resistent to collisions
int ht_get_hash(const char* s, const int buckets, const int attempt) {
    debug(("ht_get_hash(%s, %d, %d)", s, buckets, attempt));
    const int hash_a = ht_hash(s, HT_PRIME_A, buckets);
    const int hash_b = ht_hash(s, HT_PRIME_B, buckets);
    return (hash_a + (attempt * (hash_b + 1))) % buckets;
}
