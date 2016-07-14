#include "Image.h"
#include "extends.h"
#include <stdio.h>


Image* load_image(char *source, char(*get_byte)(char *source))
{
    Image *image=new(Image);

    load_TGA(source, get_byte, image);

    if(image->data)
        return image;

    free(image);
    return 0;
}


void free_image(Image *image)
{
    free(image->data);
    free(image);
}
