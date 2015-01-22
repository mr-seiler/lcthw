/* This helped: http://stackoverflow.com/a/1095006 */

#include <stdio.h>

int main()
{
    // this is a string, it's an array of characters terminated with null
    char str1[] = {
        's', 't', 'r', 'i', 'n', 'g', '\0'
    };

    // this is equivalent to the above; it makes sense if you think of it
    // as syntax sugar for the above.
    char str2[] = "string";

    // this is ALSO a string; it looks like a pointer to a char.
    // ...but it isn't.
    // It is a pointer to a constant string stored in static memory.
    // You can change the pointer, but not the actual string.
    char *str3 = "string";

    // demonstrate:
    printf("str1: %s ; str2: %s ; str3: %s", str1, str2, str3);

    // THIS, however, is an ARRAY OF STRINGS
    // it looks like a pointer to an array of chars, BUT IT ISN'T
    // (It's an array of pointers to char, like an array of the example above this one.)
    // An array of pointers to string constants in static memory.
    char *strarr[] = {
        "one", "two", "three"
    };

    return 0;
}
