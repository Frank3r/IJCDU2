/*
 *  Frantisek Sedlacek
 *  VUT FIT Brno
 *  Priklad: IJC-DU2
 *  19.04. 2023
 */

#include "htab_private.h"
#include "stdint.h"

size_t htab_hash_function(htab_key_t str) {
    /*  Hash function
 *  (http://www.cse.yorku.ca/~oz/hash.html - sdbm variant)
 */
    uint32_t h=0;     // musí mít 32 bitů
    const unsigned char *p;
    for(p=(const unsigned char*)str; *p!='\0'; p++)
        h = 65599*h + *p;
    return h;
}
