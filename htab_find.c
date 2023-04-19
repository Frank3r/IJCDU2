#include "htab.h"
#include "htab_private.h"

htab_pair_t * htab_find(const htab_t * t, htab_key_t key){
    size_t keyhash= htab_hash_function(key);
    size_t bucket= keyhash % t->arr_size;
    htab_item_t *cur_ptr=t->arr_ptr[bucket];
    while(cur_ptr!=NULL){
        if(keyhash == htab_hash_function(cur_ptr->pair.key)){
            return &cur_ptr->pair;
        }
        cur_ptr= cur_ptr->next;
    }
    return NULL;
}