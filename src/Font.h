#ifndef FONT_H_INCLUDED
#define FONT_H_INCLUDED

#include <GL/gl.h>
#include "Image.h"


typedef struct
{
    unsigned int texture_id;
    float        coords[256][4];
}
Font;


Font* load_font(char *source, char (*get_byte)(char *source));
void save_font(Image *image, Font *font, char *source, void(*write_byte)(char *source, char byte));
void print(char *message, Font *font);

#endif // FONT_H_INCLUDED
