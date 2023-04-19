#include "htab.h"
#include "htab_private.h"
#include <stdlib.h>
#include <stdio.h>

htab_t *htab_init(const size_t n){
    struct htab* tab;
    tab=malloc(sizeof(struct htab));
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
