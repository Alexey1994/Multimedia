#ifndef TGA_H_INCLUDED
#define TGA_H_INCLUDED

#include "Image.h"

void load_TGA(char *source, char(*get_byte)(char *source), Image *image);

#endif // TGA_H_INCLUDED
