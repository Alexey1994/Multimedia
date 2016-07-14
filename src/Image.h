#ifndef IMAGE_H_INCLUDED
#define IMAGE_H_INCLUDED


typedef struct
{
    unsigned int  width;
    unsigned int  height;
    unsigned int  bpp;
    char         *data;
}
Image;


Image* load_image(char *source, char(*get_byte)(char *source));
void free_image(Image *image);

#endif // IMAGE_H_INCLUDED
