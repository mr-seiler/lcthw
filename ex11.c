/* same as ex10, only using a while loop-dee-do */

#include <stdio.h>

void printStrArr(int count, char *strarr[])
{
    int i = 0; // need c99 mode to use for (int i =...) apparently
    while (i < count)
    {
        printf("#%d: %s\n", i, strarr[i]);
        i += 1;
    }
}

int main(int argc, char *argv[])
{
    // not that arv[0] is the name of the file that was executed
    printStrArr(argc, argv);

    // lets try to copy the pointers to another array in reverse order
    int realArgc = argc - 1;
    char *argvCpy[realArgc];

    int i;
    for (i = 1; i < argc; i += 1)
    {
        argvCpy[realArgc - i] = argv[i];
    }

    printStrArr(realArgc, argvCpy);

    // try to mutate a string in one of the arrays,
    // and see if it changes in both
    argvCpy[0] = "yellow";

    printStrArr(argc, argv);
    printStrArr(realArgc, argvCpy);

    // that only changed it in argvCpy, so maybe we actually copied?
    // how about the other direction...
    argv[realArgc] = "blue";

    printStrArr(argc, argv);
    printStrArr(realArgc, argvCpy);

    // conclusion - it must have actually copied the strings?
    // changing a string in one array does not change it in the other...
    // StackOverflow says C cannot assign array types at all, ever?

    return 0;
}
