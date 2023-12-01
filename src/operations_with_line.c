#include "base_struct.h"
#include <malloc.h>
#include <math.h>


void create_buffer(int8_t **s) {
    *s = calloc(sizeof(int8_t), 10);
}

struct line convertor(int8_t number) {
    int8_t* mas;
    create_buffer(&mas);
    size_t i = 8;
    while (number >= 1) {
        mas[i] = (int8_t) (number % 2);
        number = (int8_t) (number / 2);
        i--;
    }
    return (struct line) {.type1 = None, .massiv = mas};
}



void revers_sign(struct line *origin) {
    if (origin->massiv[1] == 1) { origin->massiv[1] = 0; }
    else { origin->massiv[1] = 1; }
}

void revers_save_line(struct line *origin) {
    for (size_t i = 2; i != 9; i++) {
        if (origin->massiv[i] == 1) { origin->massiv[i] = 0; }
        else { origin->massiv[i] = 1; }
    }
}

void plus_one_line(struct line *origin) {
    int8_t transfer = 1;
    for (size_t i = 8; transfer != 0; i--) {
        if (origin->massiv[i] + transfer == 2) { origin->massiv[i] = 0; }
        else {
            origin->massiv[i] = 1;
            transfer = 0;
        }
    }
}

void neg_dop_line(struct line *origin) {
    revers_save_line(origin);
    revers_sign(origin);
    plus_one_line(origin);
    if (origin->type1 == A_pr) { origin->type1 = A_dop; }
    else if (origin->type1 == B_pr) { origin->type1 = B_dop; }
}

struct line copy_line(struct line s) {
    int8_t* mas;
    create_buffer(&mas);
    for (size_t i = 0; i != 10; i++) {
        mas[i] = s.massiv[i];
    }
    return (struct line) {.type1 = s.type1, .massiv = mas};
}

int16_t unsigned_representation(struct line s) {
    int16_t tmp = 0;
    int8_t index = 7;
    for (size_t i = 1; i < 9; i++, index--) {
        tmp = (int16_t) (tmp + (int16_t) s.massiv[i] * (int16_t) pow(2, index));
    }
    return tmp;
}

int16_t signed_representation(struct line s) {
    int16_t tmp = 0;
    int8_t index = 6;
    int8_t vrem[9];
    int8_t zops = 0;
    if (s.massiv[1] == 1) {
        for (size_t i = 0; i != 9; i++) { vrem[i] = s.massiv[i]; }
        for (size_t i = 2; i != 9; i++) {
            if (vrem[i] == 1) { vrem[i] = 0; }
            else { vrem[i] = 1; }
        }
        int8_t transfer = 1;
        for (size_t i = 8; transfer != 0; i--) {
            if (vrem[i] + transfer == 2) { vrem[i] = 0; }
            else {
                vrem[i] = 1;
                transfer = 0;
            }
        }
        for (size_t i = 2; i < 9; i++, index--) {
            tmp = (int16_t) (tmp + (int16_t) vrem[i] * (int16_t) pow(2, index));
        }
        int16_t tmp2 = tmp;
        while (zops != 2) {
            tmp = (int16_t) (tmp - tmp2);
            zops++;
        }
    } else {
        for (size_t i = 2; i < 9; i++, index--) {
            tmp = (int16_t) (tmp + (int16_t) s.massiv[i] * (int16_t) pow(2, index));
        }
    }
    return tmp;
}

void creat_c(struct line *c) {
    int8_t* m;
    create_buffer(&m);
    c->massiv = m;
    c->type1 = None;
}

void clear_buffer_and_c(int8_t **buffer, struct line *c) {
    for (size_t i = 0; i != 10; i++) {
        (*buffer)[i] = 0;
        c->massiv[i] = 0;
        c->type1 = None;
    }
}

void sum(int8_t **buffer, struct line *a, struct line *b, struct line *c) {
    int8_t tmp;
    for (size_t i = 8; i > 0; i--) {
        tmp = (int8_t) ((*buffer)[i] + b->massiv[i] + a->massiv[i]);
        switch (tmp) {
            case 3:
                c->massiv[i] = 1;
                (*buffer)[i - 1] = 1;
                break;
            case 2:
                c->massiv[i] = 0;
                (*buffer)[i - 1] = 1;
                break;
            case 1:
                c->massiv[i] = 1;
                (*buffer)[i - 1] = 0;
                break;
            default:
                c->massiv[i] = 0;
                (*buffer)[i - 1] = 0;
                break;
        }
    }
    if (c->massiv[1] == 1) { c->type1 = C_dop; }
    else { c->type1 = C_pr; }
}

void all_free(struct line a_pr, struct line b_pr, struct line a_minus_dop, struct line b_minus_dop,
              int8_t *buffer, struct line c_line) {
    free(a_pr.massiv);
    free(b_pr.massiv);
    free(a_minus_dop.massiv);
    free(b_minus_dop.massiv);
    free(buffer);
    free(c_line.massiv);
}
