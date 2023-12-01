#include "operations_with_line.h"



int8_t getCF(const int8_t *buffer) {
    return buffer[0];
}

int8_t getPF(const struct line *cline) {
    int8_t tmp = 0;
    for (size_t i = 1; i != 9; i++) {
        tmp = (int8_t) (tmp + cline->massiv[i]);
    }
    if (tmp % 2 == 1) { return 0; }
    else { return 1; }
}

int8_t getAFs(const int8_t *buffer) {
    return buffer[4];
}

int8_t getZF(const struct line *c_line) {
    if (unsigned_representation(*c_line) == 0) { return 1; }
    else { return 0; }
}

int8_t getSF(const struct line *c_line) {
    return c_line->massiv[1];
}

int8_t getOF(const int8_t *buffer) {
    if (buffer[0] == buffer[1]) { return 0; }
    else { return 1; }
}