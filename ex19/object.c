// library includes
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
// headers for this source file
#include "object.h"

/* Deallocates an object.
 */
void Object_destroy(void *self)
{
    Object *obj = self;
    if (obj)
    {
        if (obj->description)
        {
            free(obj->description);
        }
        free(obj);
    }
}

/* Prints an object's description (if one is set)
 */
void Object_describe(void *self)
{
    assert(self != NULL);

    Object *obj = self;
    printf("%s.\n", obj->description);
}

/* Default initializer is a nop */
int Object_init(void *self)
{
    assert(self != NULL);
    return 1;
}

/* If subclasses do not provide overrides for move and attack,
 * then the object cannot move or attack.
 */

void *Object_move(void *self, Direction direction)
{
    printf("You can't go that direction.\n");
    return NULL;
}

int Object_attack(void *self, int damage)
{
    printf("You can't attack that.\n");
    return 0;
}

void *Object_new(size_t size, Object proto, char *description)
{
    assert(description != NULL);

    // set the default functions on the prototype as needed
    if(!proto.init) proto.init = Object_init;
    if(!proto.describe) proto.describe = Object_describe;
    if(!proto.destroy) proto.destroy = Object_destroy;
    if(!proto.attack) proto.attack = Object_attack;
    if(!proto.move) proto.move = Object_move;

    // allocate the object - could we not just use malloc(size) ?
    // (this is essentially creating an array of 1 element of size)
    // Note that we are allocating more space than needed, but using
    // a pointer of type Object...
    Object *el = calloc(1, size);
    assert(el != NULL);
    // copy the proto struct to the beginning of the new object
    *el = proto;

    // copies the string description
    el->description = strdup(description);

    // call the initializer
    if (!el->init(el))
    {
        // init returned 0, so it didn't complete properly
        el->destroy(el);
        return NULL;
    }
    else
    {
        // initialized, so return the pointer to the new object
        return el;
    }
}

