#include "../include/memory.h"
#include "../include/palette.h"
#include "../include/sprites.h"
#include "../include/keypad.h"
#include "../include/entity.h"

void init_memory_mapping(memory_mapping *memm)
{
    memm->object_memory_start = 0;
    memm->tile_4_start = 1;
}


int main(void)
{
    memory_mapping memm;
    uint32 keystates;

    volatile obj_attrs *insect_1_sprite;
    volatile obj_attrs *player_sprite;

    char bug1_str[256] =
        "aaaaaaaaaaaaaaaaaaaaaaannaaaaaaaaaaaaaaaanaaaaaaaaaaaaaaaanaaaaaaaaaaaaa"
        "aanaaaaaaaaaaaaaammmaaaaaaaaeeaaanmnmnaaaaeeedbccdnmnanaaaecbdddbddnmana"
        "eeddbdbdccdaaaanedbccdcdbdaaaaanccdcbdbddeeaaaaaacdbdcdaaaeaaaaaaadddaee"
        "aaaaaaaaaaaeeaaeaaaaaaaaaaaaeaaaaaaaaaaa";

    char character_str[256] = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
    "aaaaaaccccccaaaaaaaaccccccccccaaaaaccccccccccaaaaaaccfffffffaaaaaacccfffc"
    "ffcaaaaaaaccfffffffaaaaaaaacfffffffaaaaaaaaahhhhhhhllaaaaaaahhcechhloaaaa"
    "aaahhccchhllaaaaaaahhhhhhhaaaaaaaaahhaaahhaaaaaaaaahaaaahaaaaaa";


    init_memory_mapping(&memm);

    insect_1_sprite = create_16_16_object(bug1_str, &memm);
    player_sprite = create_16_16_object(character_str, &memm);

    Entity player_s; 
    Entity insect_1_s;
    Entity * player = &player_s;
    Entity * insect_1 = &insect_1_s;
    init_entity(player, player_sprite);
    init_entity(insect_1, insect_1_sprite);

    init_palette(object_palette_mem);

    // Set the display parameters to enable objects, and use a 1D
    // object->tile mapping
    REG_DISPLAY = 0x1000 | 0x0040;

    insect_1->x = 22;
    insect_1->y = 96;
    player->x = 100;
    player->y = 96;
    update(insect_1);
    update(player);

    int loop = 1;

    while (loop)
    {
        
        // We skip the rest of the current V-Blank, as well as the V-Draw.
		while(REG_DISPLAY_VCOUNT >= 160);
		while(REG_DISPLAY_VCOUNT <  160);

        keystates = ~REG_KEY_INPUT;  // We get the pressed keys once per frame.

        if (keystates & KEY_RIGHT) {
            move_right(player);
        }
        if (keystates & KEY_LEFT) {
            move_left(player);
        }
        if (keystates & KEY_UP) {
            move_up(player);
        } 
        if (keystates & KEY_DOWN) {
            move_down(player);
        }


        update(player);
    }

    return 0;
}
