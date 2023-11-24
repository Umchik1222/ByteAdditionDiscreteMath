/*
 * 1)
 * 2) прописать систему флагов
 * 3) переписать методы для сокращения кода
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

struct strochka {
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


struct strochka reader_plus_convertor(enum type s) {
    int8_t tmp = reading_number();
    int8_t *mas = calloc(sizeof(int8_t), 10);
    size_t i = 8;
    while (tmp >= 1) {
        mas[i] = (int8_t) (tmp % 2);
        tmp = (int8_t) (tmp / 2);
        i--;
    }
    return (struct strochka) {.type1 = s, .massiv = mas};
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

void printer(struct strochka s) {
    printf("%s ", messages[s.type1]);
    printf("%" PRId8 "|", s.massiv[1]);
    for (size_t i = 2; i != 9; i++) {
        printf("%"PRId8, (s.massiv[i]));
        //printf("%d",1%2);
    }
}

void  advanced_printer(struct strochka s) {
    printf("%s", messages[s.type1]);
    printf("%" PRId8, s.massiv[0]);
    printf("%" PRId8 "|", s.massiv[1]);
    for (size_t i = 2; i != 9; i++) {
        printf("%"PRId8, (s.massiv[i]));
    }
    printf("|%" PRId8, s.massiv[9]);
}

void revers_sign(struct strochka *origin) {
    if (origin->massiv[1] == 1) { origin->massiv[1] = 0; }
    else { origin->massiv[1] = 1; }
}


void revers_save_strochka(struct strochka *origin) {
    for (size_t i = 2; i != 9; i++) {
        if (origin->massiv[i] == 1) { origin->massiv[i] = 0; }
        else { origin->massiv[i] = 1; }
    }
}

void plus_one_strochka(struct strochka *origin) {
    int8_t transfer = 1;
    for (size_t i = 8; transfer != 0; i--) {
        if (origin->massiv[i] + transfer == 2) { origin->massiv[i] = 0; }
        else {
            origin->massiv[i] = 1;
            transfer = 0;
        }
    }
}

void neg_dop_strochka(struct strochka *origin) {
    revers_save_strochka(origin);
    revers_sign(origin);
    plus_one_strochka(origin);
    if (origin->type1 == A_pr) { origin->type1 = A_dop; }
    else if (origin->type1 == B_pr) { origin->type1 = B_dop; }
}

struct strochka copy_strochka(struct strochka s) {
    int8_t *mas = calloc(sizeof(int8_t), 10);
    for (size_t i = 0; i != 10; i++) {
        mas[i] = s.massiv[i];
    }
    return (struct strochka) {.type1 = s.type1, .massiv = mas};
}

int16_t unsigned_representation(struct strochka s) {
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

int16_t signed_representation(struct strochka s) {
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
            tmp = (int16_t)(tmp + (int16_t) vrem[i] * (int16_t) pow(2, index));
        }
        int16_t tmp2 = tmp;
        while (zops != 2) {
            tmp = (int16_t)(tmp - tmp2);
            zops++;
        }
    } else {
        for (size_t i = 2; i < 9; i++, index--) {
            tmp = (int16_t )(tmp + (int16_t) s.massiv[i] * (int16_t) pow(2, index));
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

void creat_c(struct strochka *c) {
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

void clear_buffer_and_c(int8_t **buffer, struct strochka *c) {
    for (size_t i = 0; i != 10; i++) {
        (*buffer)[i] = 0;
        c->massiv[i] = 0;
        c->type1 = None;
    }
}

void sum(int8_t **buffer, struct strochka *a, struct strochka *b, struct strochka *c) {
    int8_t tmp;
    for (size_t i = 8; i > 0; i--) {
        tmp = (int8_t)((*buffer)[i] + b->massiv[i] + a->massiv[i]);
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


void all_free(struct strochka a_pr, struct strochka b_pr, struct strochka a_minus_dop, struct strochka b_minus_dop, int8_t* buffer, struct  strochka c_strochka){
    free(a_pr.massiv);
    free(b_pr.massiv);
    free(a_minus_dop.massiv);
    free(b_minus_dop.massiv);
    free(buffer);
    free(c_strochka.massiv);
}

//void printer_of_blocks(struct strochka* a, struct strochka* b,  int8_t buffer, struct  strochka* c_strochka){

//}

int main() {
    struct strochka a_pr; // Число A
    struct strochka b_pr; // Число B
    struct strochka a_minus_dop; // Число -A в дополнительном коде
    struct strochka b_minus_dop; // Число -A в дополнительном коде
    int8_t *buffer; // Буфер для переносов
    struct strochka c_strochka; //ответ после сложения

    create_buffer(&buffer); //выделяем память в куче под буфер
    creat_c(&c_strochka); //создаем ссылку на кучу для C. Заполняем нулями


    print_start_of_program();// начинаем программу
    a_pr = reader_plus_convertor(A_pr); //Ввод первого числа
    b_pr = reader_plus_convertor(B_pr); //Ввод второго числа

    clear_buffer_and_c(&buffer, &c_strochka); // зануляем буфер и стрчку ответа

    a_minus_dop = copy_strochka(a_pr); //копируем A в переменную для -A в оп коде
    b_minus_dop = copy_strochka(b_pr); //копируем B в переменную для -B в оп коде

    neg_dop_strochka(&a_minus_dop); // Превращаем A в доп код отрицательного числа
    neg_dop_strochka(&b_minus_dop); // Превращаем B в доп код отрицательного числа

    sum(&buffer, &a_pr, &b_pr, &c_strochka);

    printer_buffer_for_sum(buffer);
    printf("   Znak   Bez_znak");
    new_line();
    printer(a_pr);
    printf("   %  " PRId16, signed_representation(a_pr));
    printf("      %  " PRId16, unsigned_representation(a_pr));
    new_line();
    printer(b_pr);
    printf("   %  " PRId16, signed_representation(b_pr));
    printf("       %  " PRId16, unsigned_representation(b_pr));
    new_line();
    printer(c_strochka);
    printf("   %  " PRId16, signed_representation(c_strochka));
    printf("      %  " PRId16, unsigned_representation(c_strochka));
    new_line();







    all_free(a_pr, b_pr, a_minus_dop, b_minus_dop, buffer, c_strochka);


    exit1();
    return 0;
}
