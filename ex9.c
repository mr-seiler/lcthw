#include <stdio.h>

/* extra functions not required by exercise.
 * I just couldn't stand it anymore.
 */

void printNumbers(int nums[])
{
    printf("numbers: %d %d %d %d\n",
            nums[0], nums[1], nums[2], nums[3]);
}

void printName(char str[])
{
    printf("name each: %c %c %c %c\n",
            str[0], str[1], str[2], str[3]);
}

void printThings(int numbers[], char name[])
{
    printNumbers(numbers);
    printName(name);
    printf("name: %s\n", name);
}

int main(int argc, char *argv[])
{
    int numbers[4] = {0};
    char name[4] = {'a'};

    printThings(numbers, name);

    numbers[0] = 1;
    numbers[1] = 2;
    numbers[2] = 3;
    numbers[3] = 4;

    name[0] = 'Z';
    name[1] = 'e';
    name[2] = 'd';
    name[3] = '\0';

    printThings(numbers, name);

    // yet another syntax for declaring strings...
    // this looks like a pointer to a char.  it isn't.
    char *another = "Sid";

    printf("another: %s\n", another);

    printf("another each: %c %c %c %c\n",
            another[0], another[1], another[2], another[3]);

    // is this a thing?  Can we cast a 4 byte char[] to an int?
    // int casted = (int)name;
    // above doesn't work b/c the array is actually a reference and
    // it's trying to cast the referenc to an integer; can we dereference it?
    int castified = (int)*another;
    // the above compiles without errors, though I'm not sure why
    // not sure if I just converted the pointer to an int, ot the char[] to an int

    printf("another cast to int: %d\n", castified);

    return 0;
}

