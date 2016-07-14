#include "Texture.h"
//#include "glext.h"

#define GL_BGR                            0x80E0
#define GL_BGRA                           0x80E1

GLuint load_texture(Image *image)
{
    GLint   out_type;
    GLuint  texture_id;

    switch(image->bpp)
    {
        case GL_RGB:  out_type=GL_BGR;  break;
        case GL_RGBA: out_type=GL_BGRA; break;
    }

    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_LINEAR_MIPMAP_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, image->bpp, image->width, image->height, 0, out_type, GL_UNSIGNED_BYTE, image->data);

    return texture_id;
}
