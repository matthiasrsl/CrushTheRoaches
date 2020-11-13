#include "../include/define.h"
#include "../include/palette.h"
#include "../include/sprites.h"

void init_memory_mapping(memory_mapping *memm)
{
    memm->object_memory_start = 0;
    memm->tile_4_start = 1;
}


int main(void)
{
    memory_mapping memm;

    volatile obj_attrs *insect_1;
    volatile obj_attrs *player;

    char bug1_str[256] =
        "aaaaaaaaaaaaaaaaaaaaaaannaaaaaaaaaaaaaaaanaaaaaaaaaaaaaaaanaaaaaaaaaaaaa"
        "aanaaaaaaaaaaaaaammmaaaaaaaaeeaaanmnmnaaaaeeedbccdnmnanaaaecbdddbddnmana"
        "eeddbdbdccdaaaanedbccdcdbdaaaaanccdcbdbddeeaaaaaacdbdcdaaaeaaaaaaadddaee"
        "aaaaaaaaaaaeeaaeaaaaaaaaaaaaeaaaaaaaaaaa";

    char character_str[256] = 
        "aaakaaaaaaakaaaaaaakkkkkkkkkaaaaaaaaakfkfkaaaaaaaaaaakkkkkaaaaaa"
        "aaaaakdddkaaaaaaaaaaakkkkkaaaaaaaaaaaakdkaaaaaaaaaaakkkdkkkaaaaaaakkk"
        "dkkkdkkkaaaaakdkdddddkdkaaaaakdkdddddkdkaaaaakkkdkkkdkkkaaaaaaakk"
        "kkkkkaaaaaaaaakkaaakkaaaaaaaakkkaaakkkaaaaaaakkkaaakkkaaaa";


    init_memory_mapping(&memm);

    insect_1 = create_16_16_object(bug1_str, &memm);
    player = create_16_16_object(character_str, &memm);


    init_palette(object_palette_mem);

    // Set the display parameters to enable objects, and use a 1D
    // object->tile mapping
    REG_DISPLAY = 0x1000 | 0x0040;

    set_object_position(insect_1, 22, 96);
    set_object_position(player, 100, 96);

    while (1)
    {
    }

    return 0;
}
