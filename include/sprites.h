#include "define.h"

volatile obj_attrs *create_16_16_object(
    char *sprite_str, memory_mapping *memm
);

static inline void set_object_position(
    volatile obj_attrs *object, int x, int y);