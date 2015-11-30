
#include "list.h"


list_t* make_list()
{
    list_t* list = (list_t*) malloc(sizeof(list_t));
    list->length = 0;
    list->data = NULL;
    return list;
}
int destory_list(list_t* list)
{
    if (list->data != NULL) {
        cell_t* cell = list->data;
        if (cell->next == list->data) { free(cell->data); free(cell); }
        while (cell->next != list->data)
        {
            free(cell->data);
            if (cell->prev != NULL)
            {
                free(cell->prev);
            }
            cell = cell->next;
        }
    }
    return 0;
}

size_t insert_elem(list_t* list, void* element, size_t index)
{
    cell_t* cell = (cell_t*)malloc(sizeof(cell_t));
    cell->data = element;

    if (list->data == NULL)
    {
        cell->prev = cell;
        cell->next = cell;
        list->data = cell;
        list->length++;
        return index;
    }
    
    cell_t* point = list->data;
    
    while (point->next != list->data && index)
    {
        point = point->next;
        index--;
    }
    
    cell->next = point->next;
    cell->next->prev = cell;
    cell->prev = point;
    point->next = cell;
    list->length++;
    
    return index;
}
int remove_elem(list_t* list, void* element)
{
    cell_t* point = list->data;
    if (point == NULL)
    {
        return -1;
    }
    
    if (list->length == 1)
    {
        if (element == point->data)
        {
            free(element);
            free(point);
            list->data = NULL;
            list->length--;
            return 0;
        }
        return -1;
    }
    
    while (point != list->data)
    {
        if (point->data == element)
        {
            free(element);
            point->next->prev = point->prev;
            point->prev->next = point->next;
            free(point);
            list->length--;
            return 0;
        }
        point = point->next;
    }
    
    return -1;
}

void* get_elem(list_t* list, int offset)
{
    if (list->data == NULL)
    {
        return NULL;
    }
    if (offset > list->length || list->data == NULL)
    {
        return NULL;
    }
    cell_t* cell = list->data;
    while (offset--)
    {
        cell = cell->next;
    }
    return cell->data;
}

size_t find_elem(list_t* list, void* element)
{
    cell_t* cell = list->data;
    
    if (!cell || (cell->next == list->data && cell->data != element) || list->length == 0 ) return list->length;
    int i = 0;
    while (cell != list->data)
    {
        if (cell->data == element)
            return i;
        i++;
        cell = cell->next;
    }
    return i;
    
}

size_t append_elem(list_t* list, void* element)
{
    if (list->data == NULL || list->length == 0) return insert_elem(list, element, 0);
    cell_t* point = list->data->prev;
    
    cell_t* cell = malloc(sizeof(cell_t));
    cell->data = element;
    cell->next = point->next;
    cell->prev = point;
    cell->next->prev = cell;
    point->next = cell;
    list->length++;
    
    return list->length;
}
