
#include "hashtable.h"
#include "list.h"

size_t HASH_TABLE_CAP[] = {
    31, 61, 127, 251, 509, 1021, 2039, 4093, 16381, 32749, 65521
};

const size_t HASH_TABLE_LEN = sizeof(HASH_TABLE_CAP) / sizeof(size_t);

typedef int (*hash_fn_t)(void*);

typedef struct hash_table_t{
    size_t size;
    size_t capacity;
    list_t** data;
    hash_fn_t fn;
} hash_table_t;

hash_table_t* make_hash_table(hash_fn_t);

int destory_hash_table(hash_table_t*);

void push_entry(hash_table_t* htable, void* obj, size_t size);

void* get_entry(hash_table_t* htable, void* key, size_t size);

int remove_entry(hash_table_t* htable, void* key, size_t size);

void* find_entry(hash_table_t* htable, void* key, size_t size);


static void initialize_hash_table(hash_table_t* hash_table)
{
    for (int i = 0; i < hash_table->capacity; i++)
    {
        hash_table->data[i] = make_list();
    }
}

hash_table_t* make_hash_table(hash_fn_t fn)
{
    hash_table_t* hash_table = (hash_table_t*)malloc(sizeof(hash_table_t));
    hash_table->capacity = 31;
    hash_table->size = 0;
    hash_table->fn = fn;
    hash_table->data = malloc(sizeof(list_t*)*hash_table->capacity);
    initialize_hash_table(hash_table);
    return hash_table;
}

int destory_hash_table(hash_table_t* htable)
{
    for (int i = 0; i < htable->capacity; i++)
    {
        if (destory_list(htable->data[i])) {
            return -1;
        }
    }
    free(htable->data);
    free(htable);
    return 0;
}

void push_entry(hash_table_t* htable, void* obj, size_t size)
{
    
}