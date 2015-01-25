#ifndef _ex19_h
#define _ex19_h

#include "object.h"


/* in addition to all the base Object attributes, the Monster type
 * also has a hit point counter.
 * Using typedef like this lets us refer to the struct type as just "Monster",
 * instead of "struct Monster"
 */
typedef struct {
    Object proto;
    int hit_points;
} Monster;

// Monster overrides these prototype methods
int Monster_attack(void *self, int damage);
int Monster_init(void *self);


/* has pointer to a monster and to adjacent rooms in each direction.
 * Any of these could be null (no enemy in this room, and/or no
 * adjacent room in a given direction)
 */
struct Room {
    Object proto;

    Monster *bad_guy;

    struct Room *north;
    struct Room *south;
    struct Room *east;
    struct Room *west;
};

/* Instead of declaring the struct inside the typedef, we can also declare a
 * "regular" struct and also use typedef, so we can refer to the struct type as
 * _either_ "struct Room" or "Room"
 */
typedef struct Room Room;

// Room overrides these prototype methods
void *Room_move(void *self, Direction direction);
int Room_attack(void *self, int damage);
int Room_init(void *self);

/* Has pointers to the starting room and the current room */
typedef struct {
    Object proto;
    Room *start;
    Room *location;
} Map;

// Map overrides these prototype methods
void *Map_move(void *self, Direction direction);
int Map_attack(void *self, int damage);
int Map_init(void *self);

#endif
