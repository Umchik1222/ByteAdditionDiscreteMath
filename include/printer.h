#ifndef PRINTER_H
#define PRINTER_H

#include "get_flags.h"
#include "operations_with_line.h"

void print_start_of_program();
void print_second_task(struct line *a_pr, int8_t *buffer, struct line *a_minus_dop, struct line *c_line);
void print_third_task(struct line *b_pr, int8_t *buffer, struct line *b_minus_dop, struct line *c_line);
void
print_first_task(int8_t *buffer, struct line *a_pr, struct line *b_pr, struct line *c_line, struct line *b_minus_dop,
                 struct line *a_minus_dop);
void new_line();                 


#endif