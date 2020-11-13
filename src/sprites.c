#include "../include/define.h"

volatile obj_attrs *create_16_16_object(char *sprite_str,
                                        memory_mapping *memm)
{
    volatile uint32 *sprite;
    uint32 pixel1, pixel2, pixel3, pixel4, pixel5, pixel6, pixel7, pixel8,
        four_pixels;
    sprite = (uint32 *)tile_mem[4][memm->tile_4_start];
    char shift = 97;
    int j;
    int tile, index_in_tile;

    for (int i = 0; i < 32; i++)
    { // For each 8-pixel block
        j = i;
        pixel1 = (uint32)(sprite_str[j * 8] - shift);
        pixel2 = (uint32)(sprite_str[j * 8 + 1] - shift);
        pixel3 = (uint32)(sprite_str[j * 8 + 2] - shift);
        pixel4 = (uint32)(sprite_str[j * 8 + 3] - shift);
        pixel5 = (uint32)(sprite_str[j * 8 + 4] - shift);
        pixel6 = (uint32)(sprite_str[j * 8 + 5] - shift);
        pixel7 = (uint32)(sprite_str[j * 8 + 6] - shift);
        pixel8 = (uint32)(sprite_str[j * 8 + 7] - shift);
        four_pixels = pixel1 + (pixel2 << 4) + (pixel3 << 8) + (pixel4 << 12) +
                      (pixel5 << 16) + (pixel6 << 20) + (pixel7 << 24) +
                      (pixel8 << 28);

        tile = (j / 16) * 2 + j % 2;
        index_in_tile = (j / 2) % 8;
        sprite[tile * 8 + index_in_tile] = four_pixels;
    }

    volatile obj_attrs *obj = &oam_mem[memm->object_memory_start];
    obj->attr0 = 0;      // 4bpp tiles, SQUARE shape
    obj->attr1 = 0x4000; // 16*16 size when using the SQUARE shape
    obj->attr2 =
        memm->tile_4_start; // Start at the fifth tile in tile block four,

    memm->object_memory_start += 1;
    memm->tile_4_start += 4;

    return obj;
}

// Set the position of an object to specified x and y coordinates
static inline void set_object_position(
    volatile obj_attrs *object, int x, int y)
{
    object->attr0 =
        (object->attr0 & ~OBJECT_ATTR0_Y_MASK) | (y & OBJECT_ATTR0_Y_MASK);
    object->attr1 =
        (object->attr1 & ~OBJECT_ATTR1_X_MASK) | (x & OBJECT_ATTR1_X_MASK);
}