#include "Font.h"
#include "stream.h"
#include "extends.h"
#include "RLE.h"


typedef struct
{
    char  *source;
    char (*get_byte)(char *source);
    char   buffer;
    char   count_buffer;
}
PixelReader;

static char read_pixel(PixelReader *reader)
{
    return stream_read_bits(reader->source, reader->get_byte, 1, &reader->buffer, &reader->count_buffer);
}

static char read_number(PixelReader *reader)
{
    return stream_read_bits(reader->source, reader->get_byte, 8, &reader->buffer, &reader->count_buffer);
}


typedef struct
{
    char         *pixels;
    unsigned int  count_pixel;
}
PixelWriter;

static void write_pixel(PixelWriter *writer, char data)
{
    writer->pixels[writer->count_pixel  ]=data*255;
    writer->pixels[writer->count_pixel+1]=data*255;
    writer->pixels[writer->count_pixel+2]=data*255;
    writer->pixels[writer->count_pixel+3]=255;
    writer->count_pixel+=4;
}


Font* load_font(char *source, char (*get_byte)(char *source))
{
    Font        *font;
    Image        image;
    PixelReader  reader;
    PixelWriter  writer;
    unsigned int image_size;

    if(!stream_next("FONT", source, get_byte))
        return 0;

    font=new(Font);

    image.width  = stream_get_uint(source, get_byte);
    image.height = stream_get_uint(source, get_byte);
    image.bpp    = GL_RGBA;
    image_size = image.width*image.height;
    image.data   = malloc(image_size*4);

    reader.source       = source;
    reader.get_byte     = get_byte;
    reader.count_buffer = 8;

    writer.count_pixel = 0;
    writer.pixels      = image.data;

    decompress_RLE(image_size, &reader, read_pixel, read_number, &writer, write_pixel);
    font->texture_id=load_texture(&image);

    return font;
}


typedef struct
{
    char         *pixels;
    unsigned int  current_pixel;
}
PixelIn;

static char get_font_pixel(PixelIn *in)
{
    char pixel=in->pixels[in->current_pixel];
    in->current_pixel+=4;
    return pixel;
}


typedef struct
{
    char   buffer;
    int    count_buffer;
    char  *source;
    void (*write_byte)(char *source, char byte)
}
PixelOut;

static void write_font_pixel(PixelOut *out, char data)
{
    stream_write_bits(data, out->source, out->write_byte, 1, &out->buffer, &out->count_buffer);
}

static void write_font_number(PixelOut *out, char data)
{
    stream_write_bits(data, out->source, out->write_byte, 8, &out->buffer, &out->count_buffer);
}


void save_font(Image *image, Font *font, char *source, void(*write_byte)(char *source, char byte))
{
    int      i;
    int      j;
    PixelIn  pixel_in;
    PixelOut pixel_out;

    stream_write(source, write_byte, "FONT", 4);
    stream_write(source, write_byte, &image->width, 4);
    stream_write(source, write_byte, &image->height, 4);

    for(i=0; i<256; i++)
        for(j=0; j<4; j++)
            stream_write(source, write_byte, &font->coords[i][j], 4);

    pixel_in.current_pixel = 3;
    pixel_in.pixels        = image->data;

    pixel_out.count_buffer = 8;
    pixel_out.source       = source;
    pixel_out.write_byte   = write_byte;

    compress_RLE(0, image->width*image->height, &pixel_in, get_font_pixel, &pixel_out, write_font_pixel, write_font_number);
}


void print(char *message, Font *font)
{

}
