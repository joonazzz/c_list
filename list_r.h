#ifndef __LIST_R__
#define __LIST_R__

/*
    Simple re-entrant list container 
    =============================

    - Re-entrant (i.e thread-safe) version of list.h
    - thread synchronization uses pthread mutex
*/

#include <pthread.h>

#include "list.h"

typedef struct List_r{
    List* list;
    pthread_mutex_t lock;
} List_r;

List_r* list_new_r(FreeFunction freeFn);
void list_destroy_r(List_r* list_r);

void list_prepend_r(List_r* list_r, void* data);
void list_append_r(List_r* list_r, void* data);
int list_remove_r(List_r* list_r, void *data);

ListNode* get_head_r(List_r* list_r);
ListNode* get_tail_r(List_r* list_r);

void list_for_each_r(List_r* list_r, ListIterator iterator);
int list_size_r(List_r* list_r);

void list_print_r(List_r* list_r);

#endif
