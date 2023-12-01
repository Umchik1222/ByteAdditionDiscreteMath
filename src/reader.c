#include "base_struct.h"
#include <stdbool.h>
#include <stdio.h>
#include <malloc.h>




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

struct line convertor(int8_t number) {
    int8_t *mas = calloc(sizeof(int8_t), 10);
    size_t i = 8;
    while (number >= 1) {
        mas[i] = (int8_t) (number % 2);
        number = (int8_t) (number / 2);
        i--;
    }
    return (struct line) {.type1 = None, .massiv = mas};
}

struct line reader_plus_convertor(enum type s) {
    int8_t tmp = reading_number();
    struct line pattern = convertor(tmp);
    pattern.type1 = s;
    return pattern;
}