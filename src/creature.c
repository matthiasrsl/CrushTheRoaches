#include "../include/creature.h"
#include "../include/sprites.h"

Creature init_creature(volatile obj_attrs * sprite, int initial_health) {
    Creature creature;
    creature.sprite = sprite;
    creature.health = initial_health;

    return creature;
}

void lose_health(Creature creature, int health_lost) {
    creature.health -= health_lost;
    if (creature.health < 0) {
        creature.health = 0;
    }
}

void set_creature_position(Creature creature, int x, int y) {
    set_object_position(creature.sprite, x, y);
}
