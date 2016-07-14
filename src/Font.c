#include "Font.h"
#include "stream.h"
#include "extends.h"


Font* load_font(char *source, char (*get_byte)(char *source))
{
    Font  *font;
    Image *image;

    if(!stream_next("FONT", source, get_byte))
        return 0;

    font=new(Font);

    image=load_image(source, get_byte);

    return font;
}


void save_font(Image *image, Font *font, char *source, void(*write_byte)(char *source, char byte))
{
    int i;
    int j;

    stream_write(source, write_byte, "FONT", 4);
    stream_write(source, write_byte, &image->width, 4);
    stream_write(source, write_byte, &image->height, 4);

    for(i=0; i<256; i++)
        for(j=0; j<4; j++)
            stream_write(source, write_byte, &font->coords[i][j], 4);
}


void print(char *message, Font *font)
{

}
