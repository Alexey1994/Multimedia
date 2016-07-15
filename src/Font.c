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
    int  i;
    int  j;
    char current_pixel;
    char previouse_pixel;
    int  chunk_count=0;

    char is_RAW=0;
    char is_RLE=0;

    stream_write(source, write_byte, "FONT", 4);
    stream_write(source, write_byte, &image->width, 4);
    stream_write(source, write_byte, &image->height, 4);

    for(i=0; i<256; i++)
        for(j=0; j<4; j++)
            stream_write(source, write_byte, &font->coords[i][j], 4);

    previouse_pixel=image->data[3];

    for(j=image->width*image->height, i=7; i<j; i+=4)
    {
        current_pixel=image->data[i];

        if(current_pixel!=previouse_pixel)
        {
            if(!chunk_count)
            {

            }
            else
            {

            }

            is_RAW=1;
            is_RLE=0;
        }
        else
        {
            if(!chunk_count)
            {

            }
            else
            {

            }

            is_RLE=1;
            is_RAW=0;
        }

        previouse_pixel=current_pixel;
    }
}


void print(char *message, Font *font)
{

}
