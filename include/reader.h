#ifndef READER_H
#define READER_H

#include "base_struct.h"
#include <stdbool.h>
#include <stdio.h>
#include <malloc.h>


struct line convertor(int8_t number);
struct line reader_plus_convertor(enum type s);

#endif