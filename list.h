#ifndef __LIST__
#define __LIST__

/*
    Simple generic list container
    =============================

    - Implemented with linked lists and void* data pointers
    - Stores data pointers in nodes, does not copy the data
    - Caller must first malloc the objects and give references when adding to list
    - When list is destroyed, list will automatically call free() on objects
        - if the object has other objects inside, caller should provide freeFunction to
          do proper memory cleanup

    - see main.c for example
*/

/* Function to free nested objects */
typedef void (*FreeFunction)(void *);

/* Function that can iterate over list*/
typedef void (*ListIterator)(void *);

typedef struct ListNode {
    void* data;
    struct ListNode* next;
    struct ListNode* prev;
} ListNode;

typedef struct {    
    ListNode* head;
    ListNode* tail;
    int size;   
    FreeFunction freeFn;
} List;

List* list_new(FreeFunction freeFn);
void list_destroy(List* list);

void list_prepend(List* list, void* data);
void list_append(List* list, void* data);
int list_remove(List* list, void* data);

ListNode* get_head(List* list);
ListNode* get_tail(List* list);

void list_for_each(List* list, ListIterator iterator);
int list_size(List* list);

void list_print(List* list);

#endif
