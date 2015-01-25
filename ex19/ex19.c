#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

#include "ex19.h"

/* Implementation of Monster type */

/* Implementation of override attack method for monster.
 * Returns 1 if the attack kills the monster.
 */
int Monster_attack(void *self, int damage)
{
    assert(self != NULL);

    // cast the pointer passed to this method to a monster
    Monster *monster = self;

    printf("You attack %s!\n", monster->proto.description);
    // alt, w/ macro:
    // printf("You attack %s!\n", monster->_(description));

    monster->hit_points -= damage;

    if (monster->hit_points > 0)
    {
        puts("It is still alive");
        return 0;
    }
    else
    {
        puts("It is dead!");
        return 1;
    }
}

int Monster_init(void *self)
{
    assert(self != NULL);

    // cast
    Monster *monster = self;
    // set initial value
    monster->hit_points = 10;
    // success
    return 1;
}

/* Literal monster prototype struct that sets Monster's init and attack methods.
 * Our Object.h macros allow us to create a new (something) from SomethingProto,
 * if this struct were not named this is would not work.
 */
Object MonsterProto = {
    .init = Monster_init,
    .attack = Monster_attack
};


/* Implementation of Room type */

void *Room_move(void *self, Direction direction)
{
    assert(self != NULL);

    Room *room = self;
    Room *next = NULL;

    if (direction == NORTH && room->north)
    {
        printf("You go north, into:\n");
        next = room->north;
    }
    else if (direction == SOUTH && room->south)
    {
        printf("You go south, into:\n");
        next = room->south;
    }
    else if (direction == EAST && room->east)
    {
        printf("You go east, into:\n");
        next = room->east;
    }
    else if (direction == WEST && room->west)
    {
        printf("You go west, into:\n");
        next = room->west;
    }
    else
    {
        printf("you can't go that direction\n");
        next = NULL;
    }

    if (next)
    {
        next->proto.describe(next);
    }

    return next;
}

int Room_attack(void *self, int damage)
{
    assert(self != NULL);

    Room *room = self;
    Monster *monster = room->bad_guy;

    if (monster)
    {
        monster->proto.attack(monster, damage);
        // shouldn't this return the value from monster->_(attack) instead???
        return 1;
    }
    else
    {
        printf("You flail in the air at nothing. (idiot...)\n");
        return 0;
    }
}

Object RoomProto = {
    .move = Room_move,
    .attack = Room_attack
};


/* Map type implementation */

void *Map_move(void *self, Direction direction)
{
    assert(self != NULL);

    Map *map = self;
    Room *location = map->location;
    Room *next = NULL;

    next = location->proto.move(location, direction);

    if (next)
    {
        map->location = next;
    }

    return next;
}

int Map_attack(void *self, int damage)
{
    assert(self != NULL);

    Map *map = self;
    Room *location = map->location;

    return location->_(attack)(location, damage);
}

int Map_init(void *self)
{
    assert(self != NULL);

    Map *map = self;

    // make some rooms
    Room *hall = NEW(Room, "The great Hall");
    Room *throne = NEW(Room, "The throne room");
    Room *arena = NEW(Room, "The arena, with the minotaur");
    Room *kitchen = NEW(Room, "Kitchen, you have the knife now");

    // put a monster in the arena
    arena->bad_guy = NEW(Monster, "The evil minotaur");

    // setup the room adjacencies
    hall->north = throne;

    throne->west = arena;
    throne->east = kitchen;
    throne->south = hall;

    arena->east = throne;

    kitchen->west = throne;

    // start in the hall.  Though I'm not sure we ever actually use the start
    // attr for anything, just the location.
    map->start = hall;
    map->location = hall;

    return 1;
}

Object MapProto = {
    .init = Map_init,
    .move = Map_move,
    .attack = Map_attack
};


/* core game logic */
int process_input(Map *game)
{
    printf("\n>");

    char in = getchar();
    getchar(); // eats newline

    // cheap, fragile solution to randomness ceiling... but it's only a game
    int damage = rand() % 4;

    switch (in)
    {
        case -1:
            printf("Bye!");
            return 0;
            break;
        case 'n':
            game->_(move)(game, NORTH);
            break;
        case 's':
            game->_(move)(game, SOUTH);
            break;
        case 'e':
            game->_(move)(game, EAST);
            break;
        case 'w':
            game->_(move)(game, WEST);
            break;
        case 'a':
            game->_(attack)(game, damage);
            break;
        case 'l':
            puts("You can go:");
            if (game->location->north) puts("NORTH");
            if (game->location->south) puts("SOUTH");
            if (game->location->east) puts("EAST");
            if (game->location->west) puts("WEST");
            break;
        default:
            printf("What?: %d\n", in);
    }

    return 1;
}

int main(int argc, char *argv[])
{
    // seed random generator w/ the current time
    srand(time(NULL));

    // create game map
    Map *game = NEW(Map, "The Hall of the Minotaur");

    printf("You enter the ");
    game->location->_(describe)(game->location);

    int go;
    do { go = process_input(game); } while (go);

    return 0;
}
