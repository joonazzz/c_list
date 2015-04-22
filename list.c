#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

List* list_new(FreeFunction freeFn)
{
    List* list = malloc(sizeof(List));
    list->size = 0;
    list->head = list->tail = NULL;
    list->freeFn = freeFn;
    return list;
}

void list_destroy(List* list)
{
    ListNode *current;
    while(list->head != NULL) {
        current = list->head;
        list->head = current->next;
        if(list->freeFn) {
            list->freeFn(current->data);
        }
        
        free(current->data);
        free(current);
    }
    free(list);
}

void list_prepend(List* list, void *data)
{
    ListNode *node = malloc(sizeof(ListNode));
    node->data = data;

    node->next = list->head;
    node->prev = NULL;
    list->head = node;
    if(node->next){
        node->next->prev = node;
    }
    
    // first node?
    if(!list->tail) {
        list->tail = list->head;
    }
    list->size++;
}

void list_append(List* list, void *data)
{
    ListNode *node = malloc(sizeof(ListNode));
    node->data = data;
    node->next = NULL;
    
    if(list->size == 0) {
        node->prev = NULL;
        list->head = list->tail = node;
    } else {
        node->prev = list->tail;
        list->tail->next = node;
        list->tail = node;
    }
    list->size++;
}

int list_remove(List* list, void* data){
    
    ListNode *current = list->head;
    while(current != NULL) {
        
        if(current->data == data){ 
            /* Update prev node or list head */
            if(current->prev){
                current->prev->next = current->next;
            }
            else{
                list->head = current->next;
            }            
            
            /* Update next node or list tail */
            if(current->next){
                current->next->prev = current->prev;
            }
            else{
                list->tail = current->prev;
            }            
            
            /* Finally free the node */
            if(list->freeFn) {
                list->freeFn(current->data);
            }        
            free(current->data);
            free(current);
            list->size--;
            return 1;
        }
        else{
            current = current->next;
        }        
    }
    return 0; /* No node was removed */
}

ListNode* get_head(List* list){
    return list->head;
}
ListNode* get_tail(List* list){
    return list->tail;
}

void list_for_each(List *list, ListIterator iterator)
{
    ListNode* node = list->head;
    while(node != NULL) {
        iterator(node->data);
        node = node->next;
    }
}

int list_size(List* list){
    return list->size;
}

void list_print(List* list){
    printf("\nList\n");
    printf("    list pointer = %p\n", list);
    printf("    list_size() = %d\n", list_size(list));
    printf("    list head = %p\n", list->head);
    printf("    list tail = %p\n", list->tail);
    ListNode* node;
    for(node = list->head; node != NULL; node = node->next){
        printf("\n");
        printf("      node->prev = %p\n", node->prev);
        printf("      node->next = %p\n", node->next);
        printf("      node->data = %p\n", node->data);
    }
    
    
}
