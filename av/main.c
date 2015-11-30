//
//  main.c
//  av
//
//  Created by Kimmy  on 11/30/15.
//  Copyright (c) 2015 TDCA. All rights reserved.
//

#include <stdio.h>
#include "list.h"

typedef struct a {
    int b;
    char c;
} a;

void printList(list_t* list) {
    cell_t* cell = list->data;
    printf("%zx, %d\n", (size_t)cell, *(int*)(cell->data));
    cell = cell->next;
    while (cell != list->data) {
        printf("%zx, %d\n", (size_t)cell, *(int*)(cell->data));
        cell = cell->next;
    }
}

int main(int argc, const char * argv[]) {
    
    list_t* list = make_list();
    
    int* i = NULL;
    
    for (int x = 0; x < 10; x++) {
        if (x == 5) remove_elem(list, i);
        i = (int*)malloc(sizeof(int));
        *i = x;
        if (x % 2) {
            insert_elem(list, i, 0);
        } else append_elem(list, i);
    }
    
    printList(list);
    
    return 0;
}
