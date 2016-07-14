#include "array.h"
#include "extends.h"


Array* array_init(int reserve)
{
    Array *array=new(Array);

    array->reserve=reserve;
    array->buffer_length=reserve;
    array->data=new_array(char*, reserve);
    array->length=0;
}


void array_push(Array *array, char *data)
{
    if(array->length==array->buffer_length)
    {
        array->buffer_length+=array->reserve;
        reallocate_array(array->data, char*, array->buffer_length);
    }

    array->data[array->length]=data;
    array->length++;
}
