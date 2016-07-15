#include "RLE.h"

#define NEW_CHUNK   1
#define RLE_SECTION 2
#define RAW_SECTION 3


void compress_RLE(RLE *rle, unsigned int length, char *in, char(*get_byte)(char *in), char *out, char(*write_data)(char *out, char data), char(*write_number)(char *out, char data))
{
    char previouse_data;
    char current_data=get_byte(in);
    char current_state=NEW_CHUNK;
    char buffer[128];
    int  count_buffer=0;
    int  i;

    for(; length; length--)
    {
        if(count_buffer==127)
        {
            switch(current_state)
            {
                case RLE_SECTION:
                    write_number(out, count_buffer+128);
                    write_data(out, previouse_data);
                    break;

                case RAW_SECTION:
                    write_number(out, count_buffer-1);

                    for(i=0; i<count_buffer; i++)
                        write_data(out, buffer[i]);
                    break;
            }

            count_buffer=0;
            current_state=NEW_CHUNK;
        }

        buffer[count_buffer]=current_data;
        previouse_data=current_data;
        current_data=get_byte(in);

        if(current_data==previouse_data)
        {
            switch(current_state)
            {
                case RLE_SECTION:
                    count_buffer++;
                    break;

                case RAW_SECTION:
                    write_number(out, count_buffer-1);

                    for(i=0; i<count_buffer; i++)
                        write_data(out, buffer[i]);

                    *buffer=current_data;
                    count_buffer=1;
                    current_state=RLE_SECTION;
                    break;

                case NEW_CHUNK:
                    count_buffer++;
                    current_state=RLE_SECTION;
                    break;
            }
        }
        else
        {
            switch(current_state)
            {
                case RLE_SECTION:
                    write_number(out, count_buffer+128);
                    write_data(out, previouse_data);

                    count_buffer=0;
                    current_state=NEW_CHUNK;
                    break;

                case RAW_SECTION:
                    count_buffer++;
                    break;

                case NEW_CHUNK:
                    count_buffer++;
                    current_state=RAW_SECTION;
                    break;
            }
        }
    }

    switch(current_state)
    {
        case RLE_SECTION:
            write_number(out, count_buffer+128);
            write_data(out, previouse_data);
            break;

        case RAW_SECTION:
            write_number(out, count_buffer-1);

            for(i=0; i<count_buffer; i++)
                write_data(out, buffer[i]);
            break;

        case NEW_CHUNK:
            write_number(out, 0);
            write_data(out, current_data);
            break;
    }
}


void decompress_RLE(int length, char *in, char(*get_byte)(char *in), char(*get_number)(char *source), char *out, char(*write_data)(char *out, char data))
{
    char chunk_count;
    char current_byte;

    while(length>0)
    {
        chunk_count=get_number(in);

        if(chunk_count>=0)
        {
            for(; chunk_count>=0; chunk_count--, length--)
                write_data(out, get_byte(in));
        }
        else
        {
            current_byte=get_byte(in);

            for(; chunk_count<=0; chunk_count--, length--)
                write_data(out, current_byte);
        }
    }
}
