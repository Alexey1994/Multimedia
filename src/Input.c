#include "Input.h"

#ifdef WIN32

#include <windows.h>

char key(char key)
{
    if(GetAsyncKeyState(key))
        return 1;
    return 0;
}

#endif //WIN32

#ifdef __linux__

#include <GL/glx.h>

extern Display        *linux_display;
static unsigned char   keymap[32];
static unsigned char   key_table[]={//0    1    2    3    4     5   6    7     8   9    a    b    c    d    e    f
                                    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x27,0x28,0x00,0x00,0x00,0x45,0x00,0x00,//0
                                    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x12,0x00,0x00,0x00,0x00,//1
                                    0x82,0x00,0x00,0xe4,0xd7,0xe2,0xd8,0xe3,0xe5,0x00,0x00,0x00,0x00,0xe7,0xe8,0x00,//2
                                    0x24,0x13,0x14,0x15,0x16,0x17,0x18,0x21,0x22,0x23,0x00,0x00,0x00,0x00,0x00,0x00,//3
                                    0x00,0x47,0x71,0x67,0x51,0x33,0x52,0x53,0x54,0x30,0x55,0x56,0x57,0x73,0x72,0x41,//4
                                    0x42,0x31,0x34,0x48,0x35,0x37,0x60,0x32,0x66,0x36,0x65,0x00,0x00,0x00,0x00,0x00,//5
                                    0xb3,0xa8,0xb1,0xb2,0xa4,0xa5,0xa6,0x98,0xa1,0xa2,0x00,0x00,0x00,0x00,0x00,0x00,//6
                                    0x84,0x85,0x86,0x87,0x88,0x91,0x92,0x93,0x94,0x95,0xb8,0xc1,0x00,0x00,0x00,0x00,//7
                                    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//8
                                    0x96,0x97,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//9
                                    0x63,0x77,0x46,0xd2,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//a
                                    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//b
                                    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//c
                                    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//d
                                    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//e
                                    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00//f
                                   };


char key(char key)
{
    unsigned char key_real_code;
    int           pos;

    XQueryKeymap(linux_display, keymap);
    key_real_code=key_table[(unsigned char)key];
    pos=1<<(key_real_code%16-1);

    if(pos&keymap[key_real_code/16])
        return 1;
    return 0;
}

#endif //LINUX

char key_up(unsigned char k)
{
    static char buf[256]={0};
    int i;

    for(i=0; i<256; i++)
    {
        if(buf[i]==1 && k==i && !key(k))
        {
            buf[i]=0;
            return 1;
        }
    }
    if(key(k)) buf[(int)k]=1;

    return 0;
}
