#include "../include/entity.h"
#include "../include/sprites.h"
#define SPEED 1

void init_entity(Entity * entity, volatile obj_attrs * sprite) {
    entity->sprite = sprite;
    entity->x = 0;
    entity->y = 0;
    entity->dir_x = 0;
    entity->dir_y = 0;
}

void update(Entity * entity) {
    set_object_position(entity->sprite, entity->x, entity->y);
}

void move_right(Entity * entity) {
    entity->x += SPEED;
    entity->dir_x = 1;
    // Disable horizontal flip.
    entity->sprite->attr1 = (entity->sprite->attr1 & 0xEFFF) | 0x0000; 
}

void move_left(Entity * entity) {
    entity->x -= SPEED;
    entity->dir_x = -1;
    // Enable horizontal flip.
    entity->sprite->attr1 = (entity->sprite->attr1 & 0xEFFF) | 0x1000; 
}

void move_up(Entity * entity) {
    entity->y -= SPEED;
    entity->dir_x = -1;
}

void move_down(Entity * entity) {
    entity->y += SPEED;
    entity->dir_y = 1;
}