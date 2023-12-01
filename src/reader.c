#include "base_struct.h"
#include "operations_with_line.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>



bool bigger_validator(char* number) {
    if (strlen(number) == 0) {
        return false;
    }
    for (int i = 0; i < strlen(number); i++) {
        if (!isdigit(number[i])) {
            printf("Letters\n");
            return false;
        }
    }

    long num = atol(number);
    if (num > 0 && num <= 127) {
        return true;
    }
    printf("Out of (0,127]\n");
    return false;
}

int8_t reading_number() {
    char number[15];  // Increase the size of the buffer
    number[0] = '\0'; // Initialize the string
    while (!bigger_validator(number)) {
        number[0] = '\0';
        for(size_t i = 1; i != 15; i++){
            number[i] = 0;
        }
        scanf("%14s", number);  // Use %14s to limit the input to 14 characters
        
    }
    return (int8_t)atol(number);
}

struct line reader_plus_convertor(enum type s) {
    int8_t tmp = reading_number();
    struct line pattern = convertor(tmp);
    pattern.type1 = s;
    return pattern;
}