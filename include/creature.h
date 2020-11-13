#include "memory.h"

typedef struct Creature {
    volatile obj_attrs * sprite;
    int health;
    int x;
    int y;
} Creature;

Creature init_creature(volatile obj_attrs * sprite, int initial_health);

void lose_health(Creature creature, int health_lost);

void update(Creature creature);