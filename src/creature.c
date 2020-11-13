#include "../include/creature.h"
#include "../include/sprites.h"

Creature init_creature(volatile obj_attrs * sprite, int initial_health) {
    Creature creature;
    creature.sprite = sprite;
    creature.health = initial_health;
    creature.x = 0;
    creature.y = 0;

    return creature;
}

void lose_health(Creature creature, int health_lost) {
    creature.health -= health_lost;
    if (creature.health < 0) {
        creature.health = 0;
    }
}

void update(Creature creature) {
    set_object_position(creature.sprite, creature.x, creature.y);
}
