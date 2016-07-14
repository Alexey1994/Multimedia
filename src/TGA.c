#include "TGA.h"
#include "extends.h"
#include "stream.h"
#include "Image.h"
#include <GL/gl.h>


void load_TGA(char *source, char(*get_byte)(char *source), Image *image)
{
    char            compressed[]   = {0,0,10,0,0,0,0,0,0,0,0,0};
    char            uncompressed[] = {0,0, 2,0,0,0,0,0,0,0,0,0};
    char            head[12];
    char            is_compressed;
    int             i;
    unsigned short  bpp;
    long long int   image_size;
    char           *image_data;
    char            current_r;
    char            current_g;
    char            current_b;
    char            current_a;
    char            chunk_count;
    char            current_color[4];

    image->data=0;

    for(i=0; i<12; i++)
        head[i]=get_byte(source);

    if(memory_equal(head, compressed, 12))
        is_compressed=1;
    else if(memory_equal(head, uncompressed, 12))
        is_compressed=0;
    else
        return;

    image->width  = stream_get_ushort(source, get_byte);
    image->height = stream_get_ushort(source, get_byte);
    bpp           = get_byte(source);
    get_byte(source);

    switch(bpp)
    {
        case 32: image->bpp=GL_RGBA; break;
        case 24: image->bpp=GL_RGB; break;
        default: return;
    }

    bpp/=8;
    image_size=image->width * image->height * bpp;
    image_data=malloc(image_size);
    image->data=image_data;

    if(is_compressed)
    {
        while(image_size>0)
        {
            chunk_count=get_byte(source);

            if(chunk_count>=0)
            {
                for(; chunk_count>=0; chunk_count--, image_size-=bpp)
                {
                    *image_data=get_byte(source); image_data++;
                    *image_data=get_byte(source); image_data++;
                    *image_data=get_byte(source); image_data++;

                    if(bpp==4)
                    {
                        *image_data=get_byte(source);
                        image_data++;
                    }
                }
            }
            else
            {
                current_r=get_byte(source);
                current_g=get_byte(source);
                current_b=get_byte(source);

                if(bpp==4)
                    current_a=get_byte(source);

                for(; chunk_count<=0; chunk_count--, image_size-=bpp)
                {
                    *image_data=current_r; image_data++;
                    *image_data=current_g; image_data++;
                    *image_data=current_b; image_data++;

                    if(bpp==4)
                    {
                        *image_data=current_a;
                        image_data++;
                    }
                }
            }
        }
    }
    else
    {
        for(; image_size; image_size--, image_data++)
            *image_data=get_byte(source);
    }
}
