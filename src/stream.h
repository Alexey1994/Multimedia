#ifndef STREAM_H_INCLUDED
#define STREAM_H_INCLUDED

char stream_next(char *string, char *source, char(*get_byte)(char *source));
unsigned int stream_get_uint(char *source, unsigned char(*get_byte)(char *source));
unsigned int stream_get_ushort(char *source, char(*get_byte)(char *source));
void stream_skip(unsigned int length, char *source, char(*get_byte)(char *source));
char memory_equal(char *data1, char *data2, int sz);

void stream_write(char *source, void(*write_byte)(char *source, char byte), char *buffer, unsigned int length);

#endif // STREAM_H_INCLUDED
