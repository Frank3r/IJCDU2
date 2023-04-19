/*
 *  Frantisek Sedlacek
 *  VUT FIT Brno
 *  Priklad: IJC-DU2
 *  19.04. 2023
 */

#include "htab.h"
#include "htab_private.h"
#include <stdlib.h>

void htab_free(htab_t * t){
    htab_clear(t);
    free(t->arr_ptr);
    free(t);
}

