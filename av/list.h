
#ifndef __av__list__
#define __av__list__

#include <stdlib.h>

typedef struct cell_t {
    struct cell_t* next;
    struct cell_t* prev;
    void* data;
} cell_t;

typedef struct list_t {
    size_t length;
    cell_t* data;
} list_t;

list_t* make_list();
int destory_list(list_t* list);

size_t insert_elem(list_t* list, void* element, size_t index);
int remove_elem(list_t* list, void* element);

void* get_elem(list_t* list, int offset);
size_t append_elem(list_t* list, void* element);

#endif
