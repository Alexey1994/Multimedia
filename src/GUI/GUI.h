#ifndef GUI_H_INCLUDED
#define GUI_H_INCLUDED

#include "../array.h"


typedef struct
{
    Array *windows;
}
GUI;


GUI* load_GUI(char *source, char(*get_byte)(char *source));
void save_GUI(char *source, void(*write_byte)(char *source, char byte), GUI *gui);

#endif // GUI_H_INCLUDED
