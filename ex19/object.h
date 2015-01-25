/* actually using header files! */

// lets us include this file indiscriminantly, b/c after the first time it
// is included _object_h will be set and subsequent includes will
// skip to the endif at EOF
#ifndef _object_h
#define _object_h

// enumerated set of travel directions
typedef enum {
    NORTH, SOUTH, EAST, WEST
} Direction;


/* This is the definition for our base object prototype.
 * Subtypes should have a pointer to an instance of this?
 */
typedef struct {
    char *description;
    // pointer to initializer
    int (*init)(void *self);
    // prints description?
    void (*describe)(void *self);
    // pointer to destructor
    void (*destroy)(void *self);
    // game-specific methods (but shared by all game objects)
    void *(*move)(void *self, Direction direction);
    int (*attack)(void *self, int damage);
} Object;

// function declarations; the function pointers in the object struct
// should point to the implementations of these functions.

int Object_init(void *self);
void Object_destroy(void *self);
void Object_describe(void *self);

void *Object_move(void *self, Direction direction);
int Object_attack(void *self, int damage);

/* Used to create a new object with the specified size, prototype
 * and description.  We'll use macros to create syntax sugar for this.
 */
void *Object_new(size_t size, Object proto, char *description);

// shorter version of Object_new:
// NEW(Room, "Hello") -> Object_new(sizeof(Room), RoomProto, "Hello")
#define NEW(T, N) Object_new(sizeof(T), T##Proto, N)

// lets us write obj->_(blah) instead of obj->proto.blah
#define _(N) proto.N

#endif
