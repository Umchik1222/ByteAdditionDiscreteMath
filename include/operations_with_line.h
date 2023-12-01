#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "base_struct.h"
#include <malloc.h>
#include <math.h>

void create_buffer(int8_t **s);
struct line convertor(int8_t number);
void revers_sign(struct line *origin);
void revers_save_line(struct line *origin);
void plus_one_line(struct line *origin);
void neg_dop_line(struct line *origin);
struct line copy_line(struct line s);
int16_t unsigned_representation(struct line s);
int16_t signed_representation(struct line s);
void creat_c(struct line *c);
void clear_buffer_and_c(int8_t **buffer, struct line *c);
void sum(int8_t **buffer, struct line *a, struct line *b, struct line *c);
void all_free(struct line a_pr, struct line b_pr, struct line a_minus_dop, struct line b_minus_dop,
              int8_t *buffer, struct line c_line);


#endif