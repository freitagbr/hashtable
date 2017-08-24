// hashtable.h

#ifndef HASHTABLE_H
#define HASHTABLE_H

typedef struct {
    char* key;
    char* val;
} ht_item;

typedef struct {
    int base;
    int size;
    int count;
    ht_item** items;
} ht_hashtable;

static ht_item* ht_item_new(const char*, const char*);

static void ht_item_del(ht_item*);

ht_hashtable* ht_new_sized(const int);

ht_hashtable* ht_new();

void ht_resize(ht_hashtable*, const int);

void ht_resize_up(ht_hashtable*);

void ht_resize_down(ht_hashtable*);

void ht_del(ht_hashtable*);

void ht_insert(ht_hashtable*, const char*, const char*);

void ht_update(ht_hashtable*, const char*, const char*);

char* ht_search(ht_hashtable*, const char*);

void ht_delete(ht_hashtable*, const char*);

#endif
