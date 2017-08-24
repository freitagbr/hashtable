// main.c

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "hashtable.h"

int main() {
    ht_hashtable* ht = ht_new();
    char* key = malloc(sizeof (char));
    for (char i = 0x20; i < 0x7F; i++) {
        memset(key, i, 1);
        ht_insert(ht, key, "yo");
        printf("key: \"%s\", value: \"%s\"\n", key, ht_search(ht, key));
    }
    ht_del(ht);
    return 0;
}
