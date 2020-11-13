#ifndef DEFINE_H
#define DEFINE_H

#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 160

#define MEM_IO 0x04000000
#define MEM_PAL 0x05000000
#define MEM_VRAM 0x06000000
#define MEM_OAM 0x07000000

#define REG_DISPLAY (*((volatile uint32 *)(MEM_IO)))
#define REG_DISPLAY_VCOUNT (*((volatile uint32 *)(MEM_IO + 0x0006)))
#define REG_KEY_INPUT (*((volatile uint32 *)(MEM_IO + 0x0130)))

#define OBJECT_ATTR0_Y_MASK 0x0FF
#define OBJECT_ATTR1_X_MASK 0x1FF

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;

typedef uint16 rgb15;

typedef struct obj_attrs
{
    uint16 attr0;
    uint16 attr1;
    uint16 attr2;
    uint16 pad;
} __attribute__((packed, aligned(4))) obj_attrs;

typedef struct memory_mapping
{
    int object_memory_start;
    int tile_4_start;
} memory_mapping;

typedef uint32 tile_4bpp[8]; // One tile: 32 bytes
typedef tile_4bpp tile_block[512];

#define oam_mem ((volatile obj_attrs *)MEM_OAM)
#define tile_mem ((volatile tile_block *)MEM_VRAM)
#define object_palette_mem ((volatile rgb15 *)(MEM_PAL + 0x200))

#endif