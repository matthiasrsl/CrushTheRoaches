#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 160

#define MEM_IO 0x04000000
#define MEM_PAL 0x05000000
#define MEM_VRAM 0x06000000
#define MEM_OAM 0x07000000

#define REG_DISPLAY (*((volatile uint32 *)(MEM_IO)))
#define REG_DISPLAY_VCOUNT (*((volatile uint32 *)(MEM_IO + 0x0006)))
#define REG_KEY_INPUT (*((volatile uint32 *)(MEM_IO + 0x0130)))

#define KEY_UP 0x0040
#define KEY_DOWN 0x0080
#define KEY_ANY 0x03FF

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

typedef struct memory_mapping {
  int object_memory_start;
  int tile_4_start;
} memory_mapping;

typedef uint32 tile_4bpp[8]; // One tile: 32 bytes
typedef tile_4bpp tile_block[512];

#define oam_mem ((volatile obj_attrs *)MEM_OAM)
#define tile_mem ((volatile tile_block *)MEM_VRAM)
#define object_palette_mem ((volatile rgb15 *)(MEM_PAL + 0x200))

void init_memory_mapping(memory_mapping * memm) {
  memm->object_memory_start = 0;
  memm->tile_4_start = 1;
}

// Form a 16-bit BGR GBA colour from three component values
static inline rgb15 RGB15(int r, int g, int b)
{
	return r | (g << 5) | (b << 10);
}

// Set the position of an object to specified x and y coordinates
static inline void set_object_position(volatile obj_attrs *object, int x,
									   int y)
{
	object->attr0 = (object->attr0 & ~OBJECT_ATTR0_Y_MASK) |
					(y & OBJECT_ATTR0_Y_MASK);
	object->attr1 = (object->attr1 & ~OBJECT_ATTR1_X_MASK) |
					(x & OBJECT_ATTR1_X_MASK);
}


volatile obj_attrs *create_16_16_object(char * sprite_str, memory_mapping * memm) {
	volatile uint32 * sprite;
	uint32 pixel1, pixel2, pixel3, pixel4, pixel5, pixel6, pixel7, pixel8, four_pixels;
	sprite = (uint32 *)tile_mem[4][memm->tile_4_start];
	char shift = 97;
	int j;
	int tile, k, l, index_in_tile;

	for (int i=0; i<32; i++) {  // For each 8-pixel block
		j = i;
		pixel1 = (uint32)(sprite_str[j*8] - shift);
		pixel2 = (uint32)(sprite_str[j*8+1] - shift);
		pixel3 = (uint32)(sprite_str[j*8+2] - shift);
		pixel4 = (uint32)(sprite_str[j*8+3] - shift);
		pixel5 = (uint32)(sprite_str[j*8+4] - shift);
		pixel6 = (uint32)(sprite_str[j*8+5] - shift);
		pixel7 = (uint32)(sprite_str[j*8+6] - shift);
		pixel8 = (uint32)(sprite_str[j*8+7] - shift);
		four_pixels = pixel1
			+ (pixel2 << 4) 
			+ (pixel3 << 8) 
			+ (pixel4 << 12) 
			+ (pixel5 << 16) 
			+ (pixel6 << 20)
			+ (pixel7 << 24)
			+ (pixel8 << 28);

		tile = (j / 16)*2 + j % 2;
		index_in_tile = (j / 2) % 8;
		k = tile / 2 + j % 8;
		l = tile % 2;
		sprite[tile*8+index_in_tile] = four_pixels;
	}

	volatile obj_attrs *obj = &oam_mem[memm->object_memory_start];
	obj->attr0 = 0;  // 4bpp tiles, SQUARE shape
	obj->attr1 = 0x4000;  // 16*16 size when using the SQUARE shape
	obj->attr2 = memm->tile_4_start;  // Start at the fifth tile in tile block four,

  memm->object_memory_start += 1;
  memm->tile_4_start += 4;

	return obj;
}

int main(void)
{
  memory_mapping memm;

	volatile obj_attrs *insect_1;
	volatile obj_attrs *insect_2;

	volatile char bug1_str[256] = "aaaaaaaaaaaaaaaaaaaaaaannaaaaaaaaaaaaaaaanaaaaaaaaaaaaaaaanaaaaaaaaaaaaaaanaaaaaaaaaaaaaammmaaaaaaaaeeaaanmnmnaaaaeeedbccdnmnanaaaecbdddbddnmanaeeddbdbdccdaaaanedbccdcdbdaaaaanccdcbdbddeeaaaaaacdbdcdaaaeaaaaaaadddaeeaaaaaaaaaaaeeaaeaaaaaaaaaaaaeaaaaaaaaaaa";


  init_memory_mapping(&memm);

	insect_1 = create_16_16_object(bug1_str, &memm);
  insect_2 = create_16_16_object(bug1_str, &memm);

	// Write the colour palette for our sprites into the first palette of
	// 16 colours in colour palette memory (this palette has index 0)
	object_palette_mem[1] = RGB15(0x55, 0x10, 0x00);
	object_palette_mem[2] = RGB15(0x80, 0x2a, 0x15);
	object_palette_mem[3] = RGB15(0xaa, 0x4e, 0x39);
	object_palette_mem[4] = RGB15(0xd4, 0x7f, 0x6a);
	object_palette_mem[5] = RGB15(0xff, 0xba, 0xaa);
	object_palette_mem[6] = RGB15(0x0f, 0x07, 0x3b);
	object_palette_mem[7] = RGB15(0x22, 0x18, 0x58);
	object_palette_mem[8] = RGB15(0x3c, 0x31, 0x76);
	object_palette_mem[9] = RGB15(0x5d, 0x53, 0x93);
	object_palette_mem[10] = RGB15(0x58, 0x7d, 0xb1);
	object_palette_mem[11] = RGB15(0x55, 0x51, 0x00);
	object_palette_mem[12] = RGB15(0x80, 0x7b, 0x15);
	object_palette_mem[13] = RGB15(0xaa, 0xa5, 0x39);
	object_palette_mem[14] = RGB15(0xd4, 0xd0, 0x6a);
	object_palette_mem[15] = RGB15(0xff, 0xfb, 0xaa);

	
	

	// Set the display parameters to enable objects, and use a 1D
	// object->tile mapping
	REG_DISPLAY = 0x1000 | 0x0040;

	set_object_position(insect_1, 22, 96);
  set_object_position(insect_2, 100, 96);

	while (1)
	{
	}

	return 0;
}
