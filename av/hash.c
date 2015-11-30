
#include "hash.h"

static int bdkr(char* base, size_t size)
{
    unsigned hash = 0;
    unsigned seed = 13;
    while (size) {
        hash = hash*seed + base[size--];
    }
    return hash & 0x7FFFFFFF;
}

int hash(void* base, size_t size)
{
    return bdkr(base, size);
}