#include "memory.h"

#ifndef SPRITES_H
#define SPRITES_H

volatile obj_attrs *create_16_16_object(
    char *sprite_str, memory_mapping *memm
);

void set_object_position(
    volatile obj_attrs *object, int x, int y);


#endif