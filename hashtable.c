#include "hashtable.h"
#include "hash.h"
#include "prime.h"
#include "debug.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>

// static item to replace deleted items
static ht_item HT_NULL_ITEM = {NULL, NULL};

// returns a new hashtable item
static ht_item* ht_item_new(const char* key, const char* val) {
    debug(("ht_item_new(%s, %s)", key, val));
    ht_item* item = malloc(sizeof(ht_item));
    item->key = strdup(key);
    item->val = strdup(val);
    return item;
}

// deletes a hashtable item
static void ht_item_del(ht_item* item) {
    debug(("ht_item_del(ht_item<key: %s, val: %s>)", item->key, item->val));
    free(item->key);
    free(item->val);
    free(item);
}

// returns a new hashtable of a certain base size
ht_hashtable* ht_new_sized(const int base) {
    debug(("ht_new_sized(%d)", base));
    ht_hashtable* ht = malloc(sizeof(ht_hashtable));
    ht->base = base;
    ht->size = next_prime(base);
    ht->count = 0;
    ht->items = calloc((size_t)ht->size, sizeof(ht_item*));
    return ht;
}

// returns a new hashtable with a size of 53
ht_hashtable* ht_new() {
    debug(("ht_new()"));
    return ht_new_sized(HT_DEFAULT_BASE_SIZE);
}

// resizes a hashtable to a new base size
void ht_resize(ht_hashtable* ht, const int base) {
    debug(("ht_resize(%d)", base));
    if (base < HT_DEFAULT_BASE_SIZE) return;

    ht_hashtable* tmp_ht = ht_new_sized(base);
    for (int i = 0; i < ht->size; i++) {
        ht_item* item = ht->items[i];
        if (item != NULL && item != &HT_NULL_ITEM) {
            ht_insert(tmp_ht, item->key, item->val);
        }
    }
    ht->base = tmp_ht->base;
    ht->count = tmp_ht->count;

    // swap size and items here so tmp_ht can be deleted
    const int tmp_size = ht->size;
    ht->size = tmp_ht->size;
    tmp_ht->size = tmp_size;

    ht_item** tmp_items = ht->items;
    ht->items = tmp_ht->items;
    tmp_ht->items = tmp_items;

    ht_del(tmp_ht);
}

// increases base size of a hashtable by factor of 2
void ht_resize_up(ht_hashtable* ht) {
    debug(("ht_resize_up(%d -> %d)", ht->base, ht->base << 1));
    ht_resize(ht, ht->base << 1);
}

// decreases base size of a hashtable by factor of 2
void ht_resize_down(ht_hashtable* ht) {
    debug(("ht_resize_down(%d -> %d)", ht->base, ht->base >> 1));
    ht_resize(ht, ht->base >> 1);
}

// deletes a hashtable
void ht_del(ht_hashtable* ht) {
    debug(("ht_del()"));
    for (int i = 0; i < ht->count; i++) {
        ht_item* item = ht->items[i];
        if (item != NULL) {
            ht_item_del(item);
        }
    }
    free(ht->items);
    free(ht);
}

// inserts a key/value pair into a hashtable
void ht_insert(ht_hashtable* ht, const char* key, const char* val) {
    debug(("ht_insert(%s, %s)", key, val));
    const int load = ht->count * 100 / ht->size;
    if (load > 70) ht_resize_up(ht);

    ht_item* item = ht_item_new(key, val);
    int hash = ht_get_hash(key, ht->size, 0);
    ht_item* cur_item = ht->items[hash];
    int i = 1;

    while (cur_item != NULL && cur_item != &HT_NULL_ITEM) {
        hash = ht_get_hash(key, ht->size, i);
        cur_item = ht->items[hash];
        i++;
    }
    debug(("hash: %d", hash));
    ht->items[hash] = item;
    ht->count++;
}

// updates a key in a hashtable with a new value
void ht_update(ht_hashtable* ht, const char* key, const char* val) {
    debug(("ht_update(%s, %s)", key, val));
    ht_item* item = ht_item_new(key, val);
    int hash = ht_get_hash(key, ht->size, 0);
    ht_item* cur_item = ht->items[hash];
    int i = 1;

    while (cur_item != NULL && cur_item != &HT_NULL_ITEM) {
        if (strcmp(key, item->key) == 0) {
            debug(("hash: %d", hash));
            ht_item_del(cur_item);
            ht->items[hash] = item;
            return;
        }
        hash = ht_get_hash(key, ht->size, i);
        cur_item = ht->items[hash];
        i++;
    }
}

// returns the value of a key in a hashtable, if it exists
char* ht_search(ht_hashtable* ht, const char* key) {
    debug(("ht_search(%s)", key));
    int hash = ht_get_hash(key, ht->size, 0);
    ht_item* item = ht->items[hash];
    int i = 0;

    while (item != NULL && item != &HT_NULL_ITEM) {
        if (strcmp(key, item->key) == 0) {
            debug(("hash: %d", hash));
            return item->val;
        }
        hash = ht_get_hash(key, ht->size, i);
        item = ht->items[hash];
        i++;
    }

    return NULL;
}

// deletes a key/value pair from a hashtable
void ht_delete(ht_hashtable* ht, const char* key) {
    debug(("ht_delete(%s)", key));
    const int load = ht->count * 100 / ht->size;
    if (load < 10) ht_resize_down(ht);

    int hash = ht_get_hash(key, ht->size, 0);
    ht_item* item = ht->items[hash];
    int i = 0;

    while (item != NULL && item != &HT_NULL_ITEM) {
        if (strcmp(key, item->key) == 0) {
            debug(("hash: %d", hash));
            ht_item_del(item);
            ht->items[hash] = &HT_NULL_ITEM;
            ht->count--;
        }
        hash = ht_get_hash(key, ht->size, i);
        item = ht->items[hash];
        i++;
    }
}
