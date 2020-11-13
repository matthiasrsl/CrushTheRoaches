#include "memory.h"

typedef struct Entity {
    volatile obj_attrs * sprite;
    int x;
    int y;
    int dir_x;
    int dir_y;
} Entity;

void init_entity(Entity * entity, volatile obj_attrs * sprite);

void move_right(Entity * entity);

void move_left(Entity * entity);

void move_up(Entity * entity);

void move_down(Entity * entity);

void update(Entity * entity);