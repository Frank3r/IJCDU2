
#include "htab.h"
#include "htab_private.h"
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

void htab_statistics(const htab_t * t){
    if(t==NULL){
        fprintf(stderr,"Nothing to show for HTAB");
    }
    unsigned double avg = (double)t->size/t->arr_size;
    unsigned int min=UINT_MAX;
    unsigned int max=0;
    fprintf(stderr,"Statistics for HTAB:\n");
    for(unsigned int i=0 ; i < t->arr_size;i++){
        count=0;
        htab_item_t *cur_ptr=t->arr_ptr[i];
        if(cur_ptr!=NULL){
            count++;
            while(cur_ptr->next!=NULL){
                cur_ptr=cur->ptr.next;
                count++;
            }
        }
        if(count>max)max=count;
        if(count<min)min=count;
    }
    fprintf(stderr,"Minimal list: %u\n",min);
    fprintf(stderr,"Average length: %f\n",avg);
    fprintf(stderr,"Maximal list: %u\n",max);
}