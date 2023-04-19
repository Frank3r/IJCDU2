#include "htab.h"
#include "htab_private.h"
#include <stdlib.h>
#include <stdio.h>

void htab_for_each(const htab_t * t, void (*f)(htab_pair_t *data)){
    htab_item_t *cur_ptr;
    htab_pair_t temp;
    char* temp_key= malloc(sizeof(char) * HTAB_KEY_LEN);
    if(temp_key==NULL){
        fprintf(stderr,"htab_for_each: could not allocate memory");
        return;
    }
    for(size_t i = 0; i < t->arr_size;i++){
        cur_ptr=t->arr_ptr[i];
        while(cur_ptr!=NULL){
            strncpy(temp_key,cur_ptr->pair.key,HTAB_KEY_LEN-1);
            temp.value=cur_ptr->pair.value;
            temp.key=temp_key;
            (*f)(&temp);
            cur_ptr= cur_ptr->next;
        }
    }
    free((void*)temp.key);
}