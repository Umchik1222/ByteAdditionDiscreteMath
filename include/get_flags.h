#ifndef FLAGS_H
#define FLAGS_H

#include "operations_with_line.h" 

int8_t getCF(const int8_t *buffer);
int8_t getPF(const struct line *cline);
int8_t getAFs(const int8_t *buffer);
int8_t getZF(const struct line *c_line);
int8_t getSF(const struct line *c_line);
int8_t getOF(const int8_t *buffer);

#endif