#include <stdio.h>

// hooray for formal parameter definitions that we don't really understand
void printStrArr(int count, char *strarr[])
{
    int i; // need c99 mode to use for (int i =...) apparently
    for (i = 0; i < count; i += 1)
    {
        printf("#%d: %s\n", i, strarr[i]);
    }
}

int main(int argc, char *argv[])
{
    // not that arv[0] is the name of the file that was executed
    printStrArr(argc, argv);

    int num_states = 4;
    char *states[] = {
        "California",
        "Oregon",
        "Washington",
        "Texas"
    };

    // declaring the size of the array AND using an initializer is wrong,
    // so don't use `int thing[1] = { 1 };`

    printStrArr(num_states, states);

    return 0;
}
