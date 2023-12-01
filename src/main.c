#include <math.h>
#include "reader.h"
#include <string.h>
#define MAX_INPUT_SIZE 100




void new_line() {
    printf("\n");
}

void exit1() {
    char tmp[MAX_INPUT_SIZE];
    new_line();
    printf("Enter 'exit' to quite\n");
    while (1) {
        scanf("%99s", tmp);
        if (strcmp(tmp, "exit") == 0) {
            break;   
        printf("Некорректный ввод\n");
        }
    }
    printf("Программа завершена");
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
    int8_t *mas = calloc(sizeof(int8_t), 10);
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

void create_buffer(int8_t **s) {
    *s = calloc(sizeof(int8_t), 10);
}

void print_start_of_program() {
    printf("Enter two numbers, separate them by pressing enter");
    new_line();
}

void creat_c(struct line *c) {
    int8_t *m = calloc(sizeof(int8_t), 10);
    c->massiv = m;
    c->type1 = None;
}

void printer_buffer_for_sum(int8_t *s) {
    printf("      ");
    for (size_t i = 0; i != 9; i++) {
        if (i == 2) { printf(" "); }
        printf("%" PRId8, s[i]);
    }
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

int8_t check_for_minus128(struct line *c_line) {
    if (c_line->massiv[1] == 1 && c_line->massiv[2] == 0 && c_line->massiv[3] == 0 && c_line->massiv[4] == 0 &&
        c_line->massiv[5] == 0 && c_line->massiv[6] == 0 && c_line->massiv[7] == 0 &&
        c_line->massiv[8] == 0 && c_line->type1 == C_dop) { return 1; }
    else { return 0; }
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

int8_t second_operand_for_second_task(int16_t a) {
    int8_t b;
    b = (int8_t) (((128 - a) + 127) / 2);
    return b;
}

int8_t second_operand_for_third_task(int16_t b) {
    int8_t a;
    a = (int8_t) (128 - b);
    return a;
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

int main() {
    struct line a_pr; // Число A
    struct line b_pr; // Число B
    struct line a_minus_dop; // Число -A в дополнительном коде
    struct line b_minus_dop; // Число -A в дополнительном коде
    int8_t *buffer; // Буфер для переносов
    struct line c_line; //ответ после сложения

    create_buffer(&buffer); //выделяем память в куче под буфер
    creat_c(&c_line); //Создаём ссылку на кучу для C. Заполняем нулями


    print_start_of_program();// начинаем программу
    a_pr = reader_plus_convertor(A_pr); //Ввод первого числа
    b_pr = reader_plus_convertor(B_pr); //Ввод второго числа

    clear_buffer_and_c(&buffer, &c_line); // Очищаем буфер и строчку ответа

    a_minus_dop = copy_line(a_pr); //копируем A в переменную для -A в оп коде
    b_minus_dop = copy_line(b_pr); //копируем B в переменную для -B в оп коде

    neg_dop_line(&a_minus_dop); // Превращаем A в доп код отрицательного числа
    neg_dop_line(&b_minus_dop); // Превращаем B в доп код отрицательного числа

    print_first_task(buffer, &a_pr, &b_pr, &c_line, &b_minus_dop, &a_minus_dop);
    print_second_task(&a_pr, buffer, &a_minus_dop, &c_line);
    print_third_task(&b_pr, buffer, &b_minus_dop, &c_line);

    all_free(a_pr, b_pr, a_minus_dop, b_minus_dop, buffer, c_line);

    exit1();
    return 0;
}
