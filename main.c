/*
 * 1)
 * 2) прописать систему флагов
 * 3)
 * 4) прописать изменение тега
 * 5)  
 *
 */


#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#include <inttypes.h>
#include <math.h>


enum type {
    A_pr = 0, A_dop, B_pr, B_dop, C_pr, C_dop, None, Asrev, Bsrev, Csrev
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
        [None] = "      ",
        [Asrev] = "Asrev ",
        [Bsrev] = "Bsrev ",
        [Csrev] = "Csrev "
};

bool my_validator(int32_t t) {
    if (t > 0 && t <= 127) { return 1; }
    else { return 0; }
}

int8_t reading_number() {
    int32_t number = 0;
    while (!my_validator(number)) {
        scanf("%" SCNd32, &number);
    }
    return (int8_t) number;
}


struct line reader_plus_convertor(enum type s) {
    int8_t tmp = reading_number();
    int8_t *mas = calloc(sizeof(int8_t), 10);
    size_t i = 8;
    while (tmp >= 1) {
        mas[i] = (int8_t) (tmp % 2);
        tmp = (int8_t) (tmp / 2);
        i--;
    }
    return (struct line) {.type1 = s, .massiv = mas};
}


void new_line() {
    printf("\n");
}

void exit1() {
    char tmp[100];
    new_line();
    printf("Enter any character");
    new_line();
    while (1) {
        scanf("%s", tmp);
        if (tmp[0] != '\0') {
            break;
        }
    }
}

void printer(struct line s) {
    printf("%s ", messages[s.type1]);
    printf("%" PRId8 "|", s.massiv[1]);
    for (size_t i = 2; i != 9; i++) {
        printf("%"PRId8, (s.massiv[i]));
        //printf("%d",1%2);
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

/*
void test_printer(int8_t s[]){
    for(size_t i = 0; i !=9; i++){
        printf("%" PRId8, s[i]);
    }
}
*/

int16_t signed_representation(struct line s) {
    int16_t tmp = 0;
    int8_t index = 6;
    int8_t vrem[9];
    int8_t zops = 0;
    if (s.massiv[1] == 1) {
        for (size_t i = 0; i != 9; i++) { vrem[i] = s.massiv[i]; }

        //test_printer(vrem);
        //new_line();

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

void sum(int8_t **buffer, struct line   *a, struct line *b, struct line *c) {
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

void printer_of_bigger_lower(int16_t a, int16_t b) {
    if (a > 0) { printf("A > 0   "); }
    else { printf("A < 0   "); }
    if (b < 0) { printf("B < 0"); }
    else { printf("B > 0"); }
}

void printer_of_blocks(struct line *a, struct line *b, int8_t *buffer, struct line *c_line) {
    int16_t a_ten = signed_representation(*a);
    int16_t b_ten = signed_representation(*b);
    printer_of_bigger_lower(a_ten, b_ten);
    new_line();
    printer_buffer_for_sum(buffer);
    printf("   Znak   Bez_znak");
    new_line();
    printer(*a);
    printf("   %  " PRId16, a_ten);
    printf("      %  " PRId16, unsigned_representation(*a));
    new_line();
    printer(*b);
    printf("   %  " PRId16, b_ten);
    printf("      %  " PRId16, unsigned_representation(*b));

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

    sum(&buffer, &a_pr, &b_pr, &c_line);

    printer_of_blocks(&a_pr, &b_pr, buffer, &c_line);


    all_free(a_pr, b_pr, a_minus_dop, b_minus_dop, buffer, c_line);


    exit1();
    return 0;
}
