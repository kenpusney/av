
#include <stdlib.h>
#include <string.h>
#include "hash.h"

static hcell_t *make_hcell(unsigned int hashcode, void *address, void *obj, unsigned size)
{
    hcell_t *cell = malloc(sizeof(hcell_t));
    cell->hash = hashcode;
    cell->v.unit = obj;
    cell->next = NULL;
    cell->key = copy_blob(address, size);
    return cell;
}

static size_t __primes[] = {
    13, 23, 31, 53, 61, 97, 193, 389, 769,
    1543, 3079, 6151, 12289, 24593,
    49157, 98317};

size_t next_prime(size_t num)
{
    int i = 0;
    while (__primes[i] < num)
        i++;
    if (i >= sizeof(__primes) / sizeof(size_t))
        return num;
    return __primes[i];
}

unsigned int hash(byte *buf, size_t len)
{
    unsigned int h = len;
    unsigned int step = (len >> 5) + 1;
    unsigned int i;
    for (i = len; i >= step; i -= step)
        h = (h ^ ((h << 5) + (h >> 2))) + buf[i - 1];
    if (h == 0)
        return 1;
    else
        return h;
}

void *copy_blob(void *buf, size_t size)
{
    size_t count = 0;
    byte *begin = buf;
    byte *dest = malloc(size + 1);
    while ((size--) + 1)
    {
        dest[count] = begin[count];
        count++;
    }
    return dest;
}

HashTable make_htable(size_t capacity, hsize_callback sizefn, hcmp_callback cmpfn)
{
    int i;
    HashTable tbl = malloc(sizeof(htable_t));
    tbl->size = next_prime(capacity);
    tbl->cmpfn = cmpfn;
    tbl->sizefn = sizefn;
    tbl->columns = malloc(sizeof(hcolunm_t) * (tbl->size));
    for (i = 0; i < tbl->size; ++i)
    {
        tbl->columns[i].cells = NULL;
    }
    return tbl;
}

static size_t __str_size_fn(void *buf)
{
    return strlen((char *)buf);
}

static int __str_cmp_fn(void *buf1, void *buf2)
{
    return strcmp((char *)buf1, (char *)buf2);
}

HashTable make_shtable(size_t size)
{
    return make_htable(size, __str_size_fn, __str_cmp_fn);
}

static size_t __int_size_fn(void *buf)
{
    return sizeof(int);
}

static int __int_cmp_fn(void *buf1, void *buf2)
{
    return *(int *)(buf1) - *(int *)(buf2);
}

HashTable make_ihtable(size_t size)
{
    return make_htable(size, __int_size_fn, __int_cmp_fn);
}

unsigned int hinsert(HashTable tbl, void *key, void *obj)
{
    //    hcmp_callback cmp = tbl->cmpfn;
    unsigned int code = hash((byte *)key, tbl->sizefn(key));
    hcolunm_t *clm = &tbl->columns[code % tbl->size];
    hcell_t *cell;
    if (clm->cells)
    {
        cell = clm->cells;
        while (cell->next)
            cell = cell->next;
        cell->next = make_hcell(code, key, obj, tbl->sizefn(key));
    }
    else
    {
        clm->cells = make_hcell(code, key, obj, tbl->sizefn(key));
    }
    return code;
}

void *hfind(HashTable tbl, void *key)
{
    int code = hash((byte *)key, tbl->sizefn(key));
    hcolunm_t *clm = &tbl->columns[code % tbl->size];
    hcell_t *cell = clm->cells;
    while (cell)
    {
        if (cell->hash == code && (tbl->cmpfn(cell->key, key) == 0))
            return cell->v.unit;
        cell = cell->next;
    }
    return NULL;
}

void *hremove(HashTable tbl, void *key)
{
    unsigned int code = hash((byte *)key, tbl->sizefn(key));
    //    hcmp_callback cmp = tbl->cmpfn;
    hcolunm_t *clm = &tbl->columns[code % tbl->size];
    hcell_t *cell = clm->cells;
    hcell_t *before = cell;
    void *data = NULL;
    if (cell && (cell->hash == code) && (tbl->cmpfn(cell->key, key)))
    {
        clm->cells = cell->next;
        data = cell->v.unit;
        free(cell->key);
        free(cell);
        return data;
    }
    while (before && (cell = before->next))
    {
        if (cell->hash == code && (tbl->cmpfn(cell->key, key)))
        {
            before->next = cell->next;
            data = cell->v.unit;
            free(cell->key);
            free(cell);
            break;
        }
        before = before->next;
    }
    return data;
}

void hdestroy(HashTable tbl)
{
    for (int i = 0; i < tbl->size; i++)
    {
        hcolunm_t *colunm = &tbl->columns[i];
        for (hcell_t *cell = colunm->cells; cell != NULL;)
        {
            hcell_t *current = cell;
            cell = cell->next;
            free(current->key);
            free(current);
        }
    }
    free(tbl->columns);
    free(tbl);
}