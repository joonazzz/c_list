#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list_r.h"

void inline unlock(List_r* l){
    pthread_mutex_unlock(&l->lock);
}
void inline lock(List_r* l){
    pthread_mutex_lock(&l->lock);
}

List_r* list_new_r(FreeFunction freeFn)
{
    
    List_r* list_r = malloc(sizeof(List_r));
    list_r->list = list_new(freeFn);
    
    if(pthread_mutex_init(&list_r->lock, NULL) != 0){
        printf("ERROR: pthread_mutex_init failed\n");
        list_destroy_r(list_r);
        return NULL;
    }    
    return list_r;
}

void list_destroy_r(List_r* list_r){
    lock(list_r);        
    list_destroy(list_r->list);
    unlock(list_r);

    pthread_mutex_destroy(&list_r->lock);
    free(list_r);
}

void list_prepend_r(List_r* list_r, void *data){
    lock(list_r);
    list_prepend(list_r->list, data);
    unlock(list_r);
}

void list_append_r(List_r* list_r, void *data){
    lock(list_r);
    list_append(list_r->list, data);
    unlock(list_r);
}

int list_remove_r(List_r* list_r, void *data){
    int retval = 0;
    
    lock(list_r);    
    retval = list_remove(list_r->list, data);
    unlock(list_r);
    
    return retval;
}

ListNode* get_head_r(List_r* list_r){
    ListNode* retval = NULL;
    
    lock(list_r);
    retval = get_head(list_r->list);
    unlock(list_r);
    
    return retval;
}

ListNode* get_tail_r(List_r* list_r){
    ListNode* retval = NULL;
    
    lock(list_r);
    retval = get_tail(list_r->list);
    unlock(list_r);
    
    return retval;
}

void list_for_each_r(List_r *list_r, ListIterator iterator){
    lock(list_r);
    list_for_each(list_r->list, iterator);
    unlock(list_r);
}

int list_size_r(List_r* list_r){
    int retval = -1;
    
    lock(list_r);
    retval = list_size(list_r->list);
    unlock(list_r);
    
    return retval;

}

void list_print_r(List_r* list_r){
    lock(list_r);
    list_print(list_r->list);
    unlock(list_r);
}

