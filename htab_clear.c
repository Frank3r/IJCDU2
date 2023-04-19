#include "htab.h"
#include "htab_private.h"
#include <stdlib.h>

void htab_clear(htab_t * t){
    for(size_t i = 0; i < t->arr_size;i++) {
        htab_item_t *cur_ptr= t->arr_ptr[i];
        htab_item_t *next_ptr= cur_ptr;
        while(next_ptr!=NULL){
            next_ptr=cur_ptr->next;
            free((void*)cur_ptr->pair.key);
            free(cur_ptr);
            cur_ptr=next_ptr;
        }
    }
}