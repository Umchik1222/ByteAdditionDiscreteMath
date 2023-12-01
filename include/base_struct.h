#ifndef BASE_STRUCT_H
#define BASE_STRUCT_H

#include <inttypes.h>

enum type {
    A_pr = 0, A_dop, B_pr, B_dop, C_pr, C_dop, None
};

struct line {
    enum type type1;
    int8_t *massiv;
};

extern const char *const messages[];

#endif