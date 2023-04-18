//
// Created by frara on 18.04.2023.
//

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "htab.h"
#include "htab_item.h"

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
        fprintf(stderr,"Error allocating htab");
        exit(1);
    }
    tab->size=0;
    tab->arr_size=n;
    // allocate array of pointers
    tab->arr_ptr=calloc(n,sizeof(struct htab_item_t*));
    if(tab->arr_ptr==NULL){
        fprintf(stderr,"Error allocating htab");
        free(tab);
        exit(0);
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
    size_t key_hash= htab_hash_function(key);
    htab_item_t *cur_ptr=NULL;
    for(size_t i = 0; i < t->arr_size;i++){
        if(t->arr_ptr[i]==NULL){ // firsthand empty check
            continue;
        }
        cur_ptr=t->arr_ptr[i];
        while(cur_ptr!=NULL){
            if(key_hash== htab_hash_function(cur_ptr->pair.key)){
                return &cur_ptr->pair;
            }
        }
    }
    return NULL;
}

