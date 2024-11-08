#include "get_flags.h"
#include "operations_with_line.h"
#include <stdio.h>


void new_line() {
    printf("\n");
}

void printer(struct line s) {
    printf("%s ", messages[s.type1]);
    printf("%" PRId8 "|", s.massiv[1]);
    for (size_t i = 2; i != 9; i++) {
        printf("%"PRId8, (s.massiv[i]));
        
    }
}

void advanced_printer(struct line s) {
    printf("%s", messages[s.type1]);
    printf("%" PRId8, s.massiv[0]);
    printf("%" PRId8 "|", s.massiv[1]);
    for (size_t i = 2; i != 9; i++) {
        printf("%"PRId8, (s.massiv[i]));
    }
    printf("|%" PRId8, s.massiv[9]);
}

void print_start_of_program() {
    printf("Enter two numbers, separate them by pressing enter");
    new_line();
}

void printer_buffer_for_sum(int8_t *s) {
    printf("      ");
    for (size_t i = 0; i != 9; i++) {
        if (i == 2) { printf(" "); }
        printf("%" PRId8, s[i]);
    }
}

void printer_of_explain(int8_t *buffer) {
    if (getCF(buffer) == 1) {
        printf("For UsI, the result is incorrect due to the resulting transfer from the higher bit.");
        new_line();
        printf("The weight of this transfer is 256.");
        new_line();
    }
    if (getOF(buffer) == 1) {
        printf("For SsI, the result is incorrect due to the resulting overflow.");
        new_line();
    }
}

void printer_of_bigger_lower(int16_t a, int16_t b) {
    if (a > 0) { printf("A > 0   "); }
    else { printf("A < 0   "); }
    if (b < 0) { printf("B < 0"); }
    else { printf("B > 0"); }
}

void printer_underlining() {
    printf("------------------ -----  ---------");
}


void
printer_of_two_or_one_c_lines(struct line *c_line, int16_t a_ten_s, int16_t b_ten_s, int16_t a_ten_u, int16_t b_ten_u) {
    printer_underlining();
    new_line();
    printer(*c_line);
    if (c_line->massiv[1] == 1) {
        printf("       ");
    } else {
        printf("    %" PRId16, signed_representation(*c_line));
        if (signed_representation(*c_line) != (a_ten_s + b_ten_s)) {
            printf("?");
        }
    }
    printf("       %" PRId16, unsigned_representation(*c_line));
    if (unsigned_representation(*c_line) != (a_ten_u + b_ten_u)) {
        printf("?");
    }
    if (c_line->massiv[1] == 1) {
        new_line();
        printer_underlining();
        new_line();
        if (check_for_minus128(c_line)) {
            c_line->type1 = C_pr;
            c_line->massiv[1] = 1;
            printer(*c_line);
            printf("    %d", -128);
            if (-128 != (a_ten_s + b_ten_s)) {
                printf("?");
            }
        } else {
            revers_save_line(c_line);
            plus_one_line(c_line);
            c_line->type1 = C_pr;
            printer(*c_line);
            revers_save_line(c_line);
            plus_one_line(c_line);
            printf("   %" PRId16, signed_representation(*c_line));
            if (signed_representation(*c_line) != (a_ten_s + b_ten_s)) {
                printf("?");
            }
        }
    }
}


void printer_start_first(struct line *a_pr, struct line *b_pr) {
    printf("1. A=%"PRId8", B=%"PRId8, unsigned_representation(*a_pr), unsigned_representation(*b_pr));
    new_line();
}

void printer_of_blocks(struct line *a, struct line *b, int8_t *buffer, struct line *c_line) {
    int16_t a_ten_s = signed_representation(*a);
    int16_t b_ten_s = signed_representation(*b);
    int16_t a_ten_u = unsigned_representation(*a);
    int16_t b_ten_u = unsigned_representation(*b);

    printer_of_bigger_lower(a_ten_s, b_ten_s);
    new_line();
    printer_buffer_for_sum(buffer);
    printf("   Znak   Bez_znak");
    new_line();
    printer(*a);
    printf("   %  " PRId16, a_ten_s);
    printf("      %  " PRId16, a_ten_u);
    new_line();
    printer(*b);
    printf("   %  " PRId16, b_ten_s);
    printf("      %  " PRId16, b_ten_u);
    new_line();

    printer_of_two_or_one_c_lines(c_line, a_ten_s, b_ten_s, a_ten_u, b_ten_u);
    new_line();
    printf("CF=%"PRId8" ZF=%"PRId8" PF=%"PRId8" AF=%"PRId8" SF=%"PRId8" OF=%"PRId8, getCF(buffer), getZF(c_line),
           getPF(c_line), getAFs(buffer), getSF(c_line), getOF(buffer));
    new_line();
    printer_of_explain(buffer);
    clear_buffer_and_c(&buffer, c_line);
    new_line();
    new_line();
}

void
print_first_task(int8_t *buffer, struct line *a_pr, struct line *b_pr, struct line *c_line, struct line *b_minus_dop,
                 struct line *a_minus_dop) {
    printer_start_first(a_pr, b_pr);
    sum(&buffer, a_pr, b_pr, c_line);
    printer_of_blocks(a_pr, b_pr, buffer, c_line);

    sum(&buffer, a_pr, b_minus_dop, c_line);
    printer_of_blocks(a_pr, b_minus_dop, buffer, c_line);

    sum(&buffer, a_minus_dop, b_pr, c_line);
    printer_of_blocks(a_minus_dop, b_pr, buffer, c_line);

    sum(&buffer, a_minus_dop, b_minus_dop, c_line);
    printer_of_blocks(a_minus_dop, b_minus_dop, buffer, c_line);
}

void print_second_task(struct line *a_pr, int8_t *buffer, struct line *a_minus_dop, struct line *c_line) {
    int8_t b = second_operand_for_second_task(unsigned_representation(*a_pr));
    struct line tmp = convertor(b);
    tmp.type1 = B_pr;
    printf("2. The rule for matching looks like this: A + B > 128, so 127 > B > 128 - A, so A = %"PRId16 ", let B = %"PRId8,
           unsigned_representation(*a_pr), unsigned_representation(tmp));
    new_line();

    sum(&buffer, a_pr, &tmp, c_line);
    printer_of_blocks(a_pr, &tmp, buffer, c_line);

    neg_dop_line(&tmp);

    sum(&buffer, a_minus_dop, &tmp, c_line);
    printer_of_blocks(a_minus_dop, &tmp, buffer, c_line);

    free(tmp.massiv);
}

void print_third_task(struct line *b_pr, int8_t *buffer, struct line *b_minus_dop, struct line *c_line) {
    int8_t a = second_operand_for_third_task(unsigned_representation(*b_pr));
    struct line tmp = convertor(a);
    tmp.type1 = A_pr;
    printf("3. The value of the number B is fixed (B = %"PRId16 "), and the value of A is selected\n"
           "according to the formula A + B = 128, according to which, when adding positive\n"
           "numbers, an overflow will be fixed, and when adding negative\n"
           "numbers, this will not be. Then A = %"PRId16".", unsigned_representation(*b_pr),
           unsigned_representation(tmp));
    new_line();

    sum(&buffer, &tmp, b_pr, c_line);
    printer_of_blocks(&tmp, b_pr, buffer, c_line);

    neg_dop_line(&tmp);

    sum(&buffer, &tmp, b_minus_dop, c_line);
    printer_of_blocks(&tmp, b_minus_dop, buffer, c_line);

    free(tmp.massiv);
}
