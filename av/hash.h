
#ifndef __av__hash__
#define __av__hash__

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef unsigned char byte;

typedef size_t (*hsize_callback)(void *);
typedef int (*hcmp_callback)(void *, void *);

typedef struct hcell_t
{
    unsigned int hash;
    void *key;
    union {
        byte *bytes;
        void *unit;
    } v;
    struct hcell_t *next;
} hcell_t;

typedef struct hcolunm_t
{
    hcell_t *cells;
} hcolunm_t;

typedef struct htable_t
{
    unsigned int size;
    hsize_callback sizefn;
    hcmp_callback cmpfn;
    hcolunm_t *columns;
} htable_t, *HashTable;

HashTable make_htable(size_t size, hsize_callback sizefn, hcmp_callback cmpfn);
HashTable make_shtable(size_t size);
HashTable make_ihtable(size_t size);
unsigned int hash(byte *buf, size_t len);
size_t next_prime(size_t num);

void *copy_blob(void *buf, size_t size);
unsigned int hinsert(HashTable tbl, void *key, void *obj);
void *hfind(HashTable tbl, void *key);
void *hremove(HashTable tbl, void *key);

void hdestroy(HashTable tbl);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif //__av__hash__
