#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define PRINT_SUCCESS() printf("%s...SUCCESS\n", __PRETTY_FUNCTION__)

#include "../list.h"

void test_list_new()
{
    List* l = list_new(NULL);
    assert(l->size == 0);
    assert(l->head == NULL);
    assert(l->tail == NULL);
    assert(l->freeFn == NULL);
    list_destroy(l);
    
    PRINT_SUCCESS();
}

void test_list_append() 
{
    
    List* l = list_new(NULL);

    int i;
    for(i = 0; i < 10; i++) {
        int* j = malloc(sizeof(int));
        *j = i;
        list_append(l, j);
    }

    assert(l->size == 10);

    int* value;
    value = get_tail(l)->data;
    assert(*value == 9);

    value = get_head(l)->data;
    assert(*value == 0);

    list_destroy(l);
    PRINT_SUCCESS();
}

void test_list_prepend()
{
    
    List* l = list_new(NULL);

    int i;
    for(i = 0; i < 10; i++) {
        int* j = malloc(sizeof(int));
        *j = i;
        list_prepend(l, j);
    }

    assert(list_size(l) == 10);

    int* value;
    value = get_tail(l)->data;
    assert(*value == 0);

    value = get_head(l)->data;
    assert(*value == 9);

    list_destroy(l);
    PRINT_SUCCESS();
}

void test_list_remove()
{
    
    List* l = list_new(NULL);

    int i;
    int* remove_these_items[5];
    int count = 0;
    /* Fill with 10 values */
    for(i = 0; i < 10; i++) {
        int* j = malloc(sizeof(int));
        *j = i;
        list_prepend(l, j);
        if(i % 2){
            
            remove_these_items[count++] = j;
        }
    }

    assert(list_size(l) == 10);

    int* value;
    value = get_tail(l)->data;
    assert(*value == 0);

    value = get_head(l)->data;
    assert(*value == 9);
    
    /* Remove 5 items and verify results */
    for(i=0; i<5; i++){
        list_remove(l, remove_these_items[i]);
    }
    assert(list_size(l) == 5);

    value = get_tail(l)->data;
    assert(*value == 0);

    value = get_head(l)->data;
    assert(*value == 8);
    
    list_destroy(l);
    PRINT_SUCCESS();
}


void test_list_operations()
{
    test_list_new();
    test_list_append();
    test_list_prepend();
    test_list_remove();
}
