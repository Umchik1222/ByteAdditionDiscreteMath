#include <inttypes.h>

enum type {
    A_pr = 0, A_dop, B_pr, B_dop, C_pr, C_dop, None
};

struct line {
    enum type type1;
    int8_t *massiv;
};

const char *const messages[] = {
        [A_pr] = "A pr. ",
        [A_dop] = "A dop.",
        [B_pr] = "B pr. ",
        [B_dop] = "B dop.",
        [C_pr] = "C pr. ",
        [C_dop] = "C dop.",
        [None] = "      "
};