/*
 *  Frantisek Sedlacek
 *  VUT FIT Brno
 *  Priklad: IJC-DU2
 *  19.04. 2023
 */

#ifndef IJCDU2_2_HTAB_PRIVATE_H
#define IJCDU2_2_HTAB_PRIVATE_H

#include "htab.h"
#define HTAB_KEY_LEN 255

struct htab_item{
    struct htab_item* next;
    struct htab_pair pair;
};
typedef struct htab_item htab_item_t;

struct htab{
    size_t size;
    size_t arr_size;
    htab_item_t **arr_ptr;
};

#endif //IJCDU2_2_HTAB_PRIVATE_H
