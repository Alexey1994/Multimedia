#ifndef EXTENDS_H_INCLUDED
#define EXTENDS_H_INCLUDED

#include <stdlib.h>

#define new(type) malloc(sizeof(type))
#define new_array(type, length) malloc(sizeof(type)*length)

#define reallocate(data, type) data=realloc(data, sizeof(type))
#define reallocate_array(data, type, length) data=realloc(data, sizeof(type)*length)

#endif // EXTENDS_H_INCLUDED
