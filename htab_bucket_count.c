/*
 *  Frantisek Sedlacek
 *  VUT FIT Brno
 *  Priklad: IJC-DU2
 *  19.04. 2023
 */


#include "htab.h"
#include "htab_private.h"

size_t htab_bucket_count(const htab_t * t){
    return t->arr_size;
}