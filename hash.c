#include "hash.h"
#include "prime.h"
#include "debug.h"

#include <string.h>
#include <math.h>

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
int ht_get_hash(const char* s, const int size, const int attempt) {
    debug(("ht_get_hash(%s, %d, %d)", s, size, attempt));
    const int hash_a = ht_hash(s, HT_PRIME_A, size);
    const int hash_b = ht_hash(s, HT_PRIME_B, size);
    return (hash_a + (attempt * (hash_b + 1))) % size;
}
