/* pointers demonstration.
 * The type syntax in this language should burn in hell.
 * Ada's is infinitely superior.
 */
#include <stdio.h>

int main(int argc, char *argv[])
{
    // create two arrays (synchronized, this should be an array of structs)
    // array of ints
    int ages[] = { 23, 43, 12, 89, 2 };
    // array of pointers to static strings
    // names[][] = {...} doesn't work.  Why not?
    char *names[] = {
        "Alan", "Frank", "Mary", "John", "Lisa"
    };

    // how many ages?
    int count = sizeof(ages) / sizeof(int);
    int i;

    /* method #1: indexing (straightforward) */
    for (i = 0; i < count; i += 1)
    {
        printf("%s has %d years alive.\n", names[i], ages[i]);
    }

    printf("---\n");

    /* method #2 using pointers somehow */

    // setup pointers to the start of the arrays
    // a pointer to an int.  cur_age and ages are now essentially
    // the same - they are a pointer to the first in a series of ints
    int *cur_age = ages;
    // a pointer to a pointer to static strings? Don't quite get this one...
    char **cur_name = names;

    // print same info w/ method #2
    for (i = 0; i < count; i += 1)
    {
        // I have literally never seen this syntax before.
        // *(ptr + n) yields the value at ptr + n, it's just like array indexing
        printf("%s is %d years old.\n", *(cur_name+i), *(cur_age+i));
    }

    printf("---\n");

    /* method #3: use the pointers to arrays like they are arrays themselves */
    for (i = 0; i < count; i += 1)
    {
        // demonstrates that arrays are just pointers, and pointers can
        // be used just like an array
        printf("%s is %d years old again.\n", cur_name[i], cur_age[i]);
    }

    printf("---\n");

    /* method #4: stupid and complex but still works. */
    for (cur_name = names, cur_age = ages;
            (cur_age - ages) < count;
            cur_name++, cur_age++)
    {
        printf("%s lived %d years so far.\n", *cur_name, *cur_age);
    }

    return 0;
}
