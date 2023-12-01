#include "reader.h"
#include "get_flags.h"
#include "printer.h"
#define MAX_INPUT_SIZE 100




void exit1() {
    char tmp[MAX_INPUT_SIZE];
    new_line();
    printf("Enter 'exit' to quite\n");
    while (1) {
        scanf_s("%99s", tmp, sizeof(tmp));
        if (strcmp(tmp, "exit") == 0) {
            break;   
        printf("Некорректный ввод\n");
        }
    }
    printf("Программа завершена");
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
