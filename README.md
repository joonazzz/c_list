# list - Generic linked list for holding any data for C language. 

Tired of always writing a new linked list implementation for your data? Check this simple example how this works.

```C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

typedef struct Car{    
    char* name; 
    int prize;
    int speed;
} Car;

void print_car(void* car_data){
    Car* c = (Car*) car_data;
    printf("\nc->name = %s\n", c->name);
    printf("c->speed = %d\n", c->speed);
    printf("c->prize = %d €\n", c->prize);    
}

void car_free_func(void* car_data){
    Car* c = (Car*) car_data;
    free(c->name);
}


int main(int argc, char** argv){
    
    printf("Testing generic list\n");
    
    Car* car1 = malloc(sizeof(Car));
    car1->prize = 1000;
    car1->speed = 100;
    car1->name = strdup("Seat");        /* Strdup allocates from heap, we need to free name somewhere */

    Car* car2 = malloc(sizeof(Car));
    car2->prize = 2000;
    car2->speed = 200;
    car2->name = strdup("Audi");

    Car* car3 = malloc(sizeof(Car));
    car3->prize = 3000;
    car3->speed = 300;
    car3->name = strdup("Ferrari");

    
    List* mylist = list_new(car_free_func); /* Pass the car cleanup function so we can free the car name pointer */
    list_append(mylist, car1);
    list_append(mylist, car2);
    list_append(mylist, car3);
        
    /* Test list iterator function */
    list_for_each(mylist, print_car);    
        
    list_remove(mylist, car2);

    list_for_each(mylist, print_car);    
    
    list_destroy(mylist);
        
    return 0;
}
```
