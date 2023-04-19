cmake_minimum_required(VERSION 3.25)
project(IJCDU2_2 C)

set(CMAKE_C_STANDARD 11)

add_executable(IJCDU2_2 wordcount.c htab.h htab_hash.c htab_private.h htab_init.c htab_size.c htab_bucket_count.c htab_find.c htab_lookup_add.c htab_erase.c htab_for_each.c htab_clear.c htab_free.c)
