#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define PRINT_SUCCESS() printf("%s...SUCCESS\n", __PRETTY_FUNCTION__)

#include "../list_r.h"

void test_list_new_r()
{
    List_r* l = list_new_r(NULL);
    assert(l->list->size == 0);
    assert(l->list->head == NULL);
    assert(l->list->tail == NULL);
    assert(l->list->freeFn == NULL);
    list_destroy_r(l);    
    PRINT_SUCCESS();
}

void test_list_append_r() 
{
    
    List_r* l = list_new_r(NULL);

    int i;
    for(i = 0; i < 10; i++) {
        int* j = malloc(sizeof(int));
        *j = i;
        list_append_r(l, j);
    }

    assert(list_size_r(l) == 10);

    int* value;
    value = get_tail_r(l)->data;
    assert(*value == 9);

    value = get_head_r(l)->data;
    assert(*value == 0);

    list_destroy_r(l);
    PRINT_SUCCESS();
}

void test_list_prepend_r()
{
    
    List_r* l = list_new_r(NULL);

    int i;
    for(i = 0; i < 10; i++) {
        int* j = malloc(sizeof(int));
        *j = i;
        list_prepend_r(l, j);
    }

    assert(list_size_r(l) == 10);

    int* value;
    value = get_tail_r(l)->data;
    assert(*value == 0);

    value = get_head_r(l)->data;
    assert(*value == 9);

    list_destroy_r(l);
    PRINT_SUCCESS();
}

void test_list_remove_r()
{
    
    List_r* l = list_new_r(NULL);

    int i;
    int* remove_these_items[5];
    int count = 0;
    /* Fill with 10 values */
    for(i = 0; i < 10; i++) {
        int* j = malloc(sizeof(int));
        *j = i;
        list_prepend_r(l, j);
        if(i % 2){
            remove_these_items[count++] = j;
        }
    }

    assert(list_size_r(l) == 10);

    int* value;
    value = get_tail_r(l)->data;
    assert(*value == 0);

    value = get_head_r(l)->data;
    assert(*value == 9);
    
    /* Remove 5 items and verify results */
    for(i=0; i<5; i++){
        list_remove_r(l, remove_these_items[i]);
    }
    assert(list_size_r(l) == 5);

    value = get_tail_r(l)->data;
    assert(*value == 0);

    value = get_head_r(l)->data;
    assert(*value == 8);
    
    list_destroy_r(l);
    PRINT_SUCCESS();
}






void test_list_operations_r()
{
    test_list_new_r();
    test_list_append_r();
    test_list_prepend_r();
    test_list_remove_r();

}
