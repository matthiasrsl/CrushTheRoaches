#include "../include/memory.h"

// Init the WRAM by setting the heap pointer to the beginning of the 
// on-board wram.
void init_wram() {
    uint32 * heap_pointer = (uint32 *)HEAP_POINTER;
    *heap_pointer = 0;
}

// Allocates size bytes of memory on the on-board WRAM.
void * alloc(int size) {
    uint32 * heap_pointer = (uint32 *)HEAP_POINTER;
    void * address = (void*)*heap_pointer;
    *heap_pointer += (uint32)size;
    return address;
}