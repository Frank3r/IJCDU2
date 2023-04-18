//
// Created by frara on 18.04.2023.
//

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "htab.h"
#include "htab_item.h"
#define KEY_LEN 255

struct htab{
    size_t size;
    size_t arr_size;
    htab_item_t **arr_ptr;
};

/*  Hash function
 *  (http://www.cse.yorku.ca/~oz/hash.html - sdbm variant)
 */
size_t htab_hash_function(htab_key_t str) {
    uint32_t h=0;     // musí mít 32 bitů
    const unsigned char *p;
    for(p=(const unsigned char*)str; *p!='\0'; p++)
        h = 65599*h + *p;
    return h;
}

htab_t *htab_init(const size_t n){
    struct htab* tab;
    tab= malloc(sizeof(struct htab));
    if(tab==NULL){
        fprintf(stderr,"htab_init: Error allocating htab");
        return NULL;
    }
    tab->size=0;
    tab->arr_size=n;
    // allocate array of pointers
    tab->arr_ptr=calloc(n,sizeof(struct htab_item_t*));
    if(tab->arr_ptr==NULL){
        fprintf(stderr,"htab_init: Error allocating htab");
        free(tab);
        return NULL;
    }
    return tab;
}

size_t htab_size(const htab_t * t){
    return t->size;
}

size_t htab_bucket_count(const htab_t * t){
    return t->arr_size;
}

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
    temp_item->pair.key=malloc(sizeof(char) * KEY_LEN);
    if(temp_item->pair.key==NULL){
        fprintf(stderr,"htab_lookup_add: Could not allocate key string");
        return NULL;
    }
    temp_item->next=NULL;
    strcpy(temp_item->pair.key,key);
    temp_item->pair.value=1;

    size_t keyhash= htab_hash_function(key);
    htab_item_t *cur_ptr=t->arr_ptr[keyhash%t->arr_size];
    while(cur_ptr->next!=NULL)cur_ptr=cur_ptr->next;
    cur_ptr->next=temp_item;
    t->size++;
    return &temp_item->pair;
}

bool htab_erase(htab_t * t, htab_key_t key){
    size_t keyhash= htab_hash_function(key);
    size_t bucket= keyhash % t->arr_size;
    htab_item_t *cur_ptr=t->arr_ptr[bucket];
    htab_item_t *prev_ptr=t->arr_ptr[bucket];
    while(cur_ptr!=NULL){
        if(keyhash == htab_hash_function(cur_ptr->pair.key)){
            prev_ptr->next=cur_ptr->next;
            free(cur_ptr->pair.key);
            t->size--;
            return true;
        }
        prev_ptr=cur_ptr;
        cur_ptr= cur_ptr->next;
    }
    return false;
}

void htab_for_each(const htab_t * t, void (*f)(htab_pair_t *data)){
    htab_item_t *cur_ptr;
    htab_pair_t temp;
    temp.key= malloc(sizeof(char)*KEY_LEN);
    if(temp.key==NULL){
        fprintf(stderr,"htab_for_each: could not allocate memory");
        return;
    }
    for(size_t i = 0; i < t->arr_size;i++){
        cur_ptr=t->arr_ptr[i];
        while(cur_ptr!=NULL){
            strcpy(temp.key,cur_ptr->pair.key);
            (*f)(&temp);
            cur_ptr= cur_ptr->next;
        }
    }
    free(temp.key);
}

void htab_clear_recursive(htab_item_t *item){
    if(item->next!=NULL){
        htab_clear_recursive(item->next);
    }
    free(item->pair.key);
    free(item);
}

void htab_clear(htab_t * t){
    htab_item_t *cur_ptr;
    for(size_t i = 0; i < t->arr_size;i++) {
        cur_ptr = t->arr_ptr[i];
        htab_clear_recursive(cur_ptr);
    }
}

void htab_free(htab_t * t){
    htab_clear(t);
    free(t->arr_ptr);
    free(t);
}



