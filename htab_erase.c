#include "htab.h"
#include "htab_private.h"
#include <stdlib.h>

bool htab_erase(htab_t * t, htab_key_t key){
    size_t keyhash= htab_hash_function(key);
    size_t bucket= keyhash % t->arr_size;
    htab_item_t *cur_ptr=t->arr_ptr[bucket];
    htab_item_t *prev_ptr=t->arr_ptr[bucket];
    while(cur_ptr!=NULL){
        if(keyhash == htab_hash_function(cur_ptr->pair.key)){
            prev_ptr->next=cur_ptr->next; // does not matter if its NULL
            free((void*)cur_ptr->pair.key);
            free(cur_ptr);
            t->size--;
            return true;
        }
        prev_ptr=cur_ptr;
        cur_ptr= cur_ptr->next;
    }
    return false;
}