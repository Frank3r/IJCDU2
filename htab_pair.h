//
// Created by frara on 18.04.2023.
//

#ifndef IJCDU2_2_HTAB_PAIR_H
#define IJCDU2_2_HTAB_PAIR_H

#include "htab.h"

struct htab_item{
    struct htab_pair* next;
    struct htab_pair htabPair;
};

#endif //IJCDU2_2_HTAB_PAIR_H
