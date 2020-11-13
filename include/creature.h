#include "memory.h"

typedef struct Creature {
    volatile obj_attrs * sprite;
    int health;
} Creature;

Creature init_creature(volatile obj_attrs * sprite, int initial_health);

void lose_health(Creature creature, int health_lost);

void set_creature_position(Creature creature, int x, int y);