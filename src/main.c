#include "Input.h"
#include "Texture.h"
#include <GL/gl.h>
#include <stdio.h>
#include "RLE.h"
#include "Font.h"


GLuint  texture_id;
Image  *image;
FILE   *f;
Font   *font;

void draw()
{
    static char once=1;

    if(once)
    {
        //f=fopen("a.tga", "rb");
        //image=load_image(f, fgetc);
        //texture_id=load_texture(image);
        //free_image(image);
        //fclose(f);

        f=fopen("a.font", "rb");
        font=load_font(f, fgetc);
        fclose(f);

        once=0;
    }

    glBindTexture(GL_TEXTURE_2D, font->texture_id);
    glColor3f(1,1,1);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(0.0f, 0.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex2f(1.0f, 0.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex2f(1.0f, 1.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(0.0f, 1.0f);
    glEnd();
}


void write_byte(char *source, char data)
{
    fputc(data, source);
}

int main()
{
    /*
    char buffer;
    int  count=8;

    f=fopen("GUI.cbp", "rb");

    printf("%x", stream_read_bits(f, fgetc, 8, &buffer, &count));
    printf(" %x", stream_read_bits(f, fgetc, 8, &buffer, &count));
    printf(" %x", stream_read_bits(f, fgetc, 8, &buffer, &count));
    printf(" %x", stream_read_bits(f, fgetc, 8, &buffer, &count));
    fclose(f);
    */

    /*
    FILE *f2;

    f2=fopen("a.tga", "rb");
    f=fopen("out.rle", "wb");
    compress_RLE(0, 36590, f2, fgetc, f, write_byte, write_byte);
    fclose(f);
    fclose(f2);

    f2=fopen("original", "wb");
    f=fopen("out.rle", "rb");
    decompress_RLE(36590, f, fgetc, fgetc, f2, write_byte);
    */

    Font font;
    Image *image=load_image(fopen("a.tga", "rb"), fgetc);
    f=fopen("a.font", "wb");
    save_font(image, &font, f, write_byte);
    fclose(f);

    init_graphic(draw);

    for(;;){}

    return 0;
}
