#include "stream.h"


char memory_equal(char *data1, char *data2, int sz)
{
    for(; sz; sz--, data1++, data2++)
        if(*data1!=*data2)
            return 0;

    return 1;
}


char stream_next(char *string, char *source, char(*get_byte)(char *source))
{
    char is_contains=1;

    for(; *string; string++)
        if(*string!=get_byte(source))
            is_contains=0;

    return is_contains;
}


unsigned int stream_get_uint(char *source, unsigned char(*get_byte)(char *source))
{
    unsigned int   num;
    unsigned char *num_iterrator=&num;
    int            i;

    for(i=0; i<4; i++, num_iterrator++)
        *num_iterrator=get_byte(source);

    return num;
}


unsigned int stream_get_ushort(char *source, char(*get_byte)(char *source))
{
    unsigned short  num;
    unsigned char  *num_iterrator=&num;
    int             i;

    for(i=0; i<2; i++, num_iterrator++)
        *num_iterrator=get_byte(source);

    return num;
}


void stream_skip(unsigned int length, char *source, char(*get_byte)(char *source))
{
    for(; length; length--)
        get_byte(source);
}


void stream_write(char *source, void(*write_byte)(char *source, char byte), char *buffer, unsigned int length)
{
    for(; length; buffer++,length--)
        write_byte(source, *buffer);
}


char stream_read_bits(char *source, char(*get_byte)(char *source), int length, char *buffer, int *count_buffer)
{
    int  i;
    int  counter=0;
    char bits=0;

    for(; length; length--, counter++, (*count_buffer)++)
    {
        if(*count_buffer==8)
        {
            *buffer=get_byte(source);
            *count_buffer=0;
        }

        bits|=(1&(*buffer>>*count_buffer))<<counter;
    }

    return bits;
}


char stream_write_bits(char bits, char *source, void(*write_byte)(char *source, char data), int length, char *buffer, int *count_buffer)
{
    int  i;
    int  counter=0;

    for(; length; length--, counter++, (*count_buffer)++)
    {
        if(*count_buffer==8)
        {
            write_byte(source, *buffer);
            *count_buffer=0;
            *buffer=0;
        }

        *buffer|=(1&(bits>>counter))<<*count_buffer;
    }

    return bits;
}
