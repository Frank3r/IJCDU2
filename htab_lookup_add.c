#include "htab.h"
#include "htab_private.h"
#include <stdio.h>
#include <stdlib.h>

htab_pair_t * htab_lookup_add(htab_t * t, htab_key_t key){
    htab_pair_t* temp_pair = htab_find(t, key);
    if(temp_pair != NULL){
        temp_pair->value++;
        return temp_pair;
    }
    htab_item_t* temp_item=malloc(sizeof(htab_item_t));
    if(temp_item==NULL){
        fprintf(stderr,"htab_lookup_add: Could not allocate htab_pair");
        return NULL;
    }
    char* temp_key=malloc(sizeof(char) * HTAB_KEY_LEN);
    if(temp_key==NULL){
        fprintf(stderr,"htab_lookup_add: Could not allocate key string");
        return NULL;
    }
    temp_item->next=NULL;
    strncpy(temp_key,key,HTAB_KEY_LEN-1);
    temp_item->pair.key=temp_key;
    temp_item->pair.value=1;

    size_t keyhash= htab_hash_function(key);
    htab_item_t *cur_ptr=t->arr_ptr[keyhash%t->arr_size];
    if(cur_ptr!=NULL) {
        while (cur_ptr->next != NULL)cur_ptr = cur_ptr->next;
        cur_ptr->next=temp_item;
    }else{
        t->arr_ptr[keyhash%t->arr_size]=temp_item;
    }
    t->size++;
    return &temp_item->pair;
}