#include "../include/memory.h"

// Form a 16-bit BGR GBA colour from three component values
rgb15 RGB15(uint32 rgb) {
    return (rgb15)(((rgb & 0x00f80000) >> 19) | ((rgb & 0x0000f800) >> 6) | ((rgb & 0x000000f8) << 7));
}

// Initialize the first palette of the memory with desired colors.
// This palette has index 0.
void init_palette(volatile rgb15 * palette) {
    palette[0] = RGB15(0x000000);
    palette[1] = RGB15(0x551000);
    palette[2] = RGB15(0x802a15);
    palette[3] = RGB15(0xaa4e39);
    palette[4] = RGB15(0xd47f6a);
    palette[5] = RGB15(0xffbaaa);
    palette[6] = RGB15(0x0f073b);
    palette[7] = RGB15(0x221858);
    palette[8] = RGB15(0x3c3176);
    palette[9] = RGB15(0x5d5393);
    palette[10] = RGB15(0x857db1);
    palette[11] = RGB15(0x555100);
    palette[12] = RGB15(0x807b15);
    palette[13] = RGB15(0xaaa539);
    palette[14] = RGB15(0xd4d06a);
    palette[15] = RGB15(0xfffbaa);
}