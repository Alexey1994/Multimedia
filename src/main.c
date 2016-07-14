#include "Input.h"
#include "Texture.h"
#include <GL/gl.h>
#include <stdio.h>


GLuint  texture_id;
Image  *image;
FILE   *f;

void draw()
{
    static char once=1;

    if(once)
    {
        f=fopen("a.tga", "rb");
        image=load_image(f, fgetc);
        texture_id=load_texture(image);
        free_image(image);
        fclose(f);

        once=0;
    }

    glBindTexture(GL_TEXTURE_2D, texture_id);
    glColor3f(1,1,1);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(0.0f, 0.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex2f(1.0f, 0.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex2f(1.0f, 1.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(0.0f, 1.0f);
    glEnd();
}


int main()
{
    init_graphic(draw);

    for(;;){}

    return 0;
}
