#ifndef RLE_H_INCLUDED
#define RLE_H_INCLUDED

typedef struct
{

}
RLE;


void compress_RLE(RLE          *rle,
                  unsigned int  length,
                  char         *in,
                  char        (*get_byte)(char *in),
                  char         *out,
                  char        (*write_data)(char *out, char data),
                  char        (*write_number)(char *out, char data));

void decompress_RLE(int    length,
                    char  *in,
                    char (*get_byte)(char *in),
                    char (*get_number)(char *source),
                    char  *out,
                    char (*write_data)(char *out, char data));

#endif // RLE_H_INCLUDED
