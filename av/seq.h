
#ifndef __av_sstr_h__
#define __av_sstr_h__

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct sstr_t
{
    size_t size;
    unsigned char *bytes;
} sstr_t, *SimpleString;

typedef struct buffer_t
{
    size_t size;
    size_t index;
    unsigned char *bytes;
} buffer_t, *Buffer;

typedef struct sarray_t
{
    size_t count;
    size_t capacity;
    size_t elem_size;
    byte *base;
} sarray_t, *Array;

typedef struct cell_t
{
    struct cell_t *next;
    struct cell_t *prev;
    void *data;
} cell_t;

typedef struct list_t
{
    size_t length;
    cell_t *data;
} list_t, *LinkedList;

list_t *make_list();
int destory_list(list_t *list);

size_t insert_elem(list_t *list, void *element, size_t index);
int remove_elem(list_t *list, void *element);

void *get_elem(list_t *list, int offset);
size_t append_elem(list_t *list, void *element);

#ifdef __cplusplus
} // __cplusplus
#endif
#endif // __av_sstr_h__