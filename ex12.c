#include <stdio.h>

int main(int argc, char *argv[])
{

    if (argc == 2)
    {
        printf("Here's your one measly argument: %s\n", argv[1]);
    }
    else if (argc == 3)
    {
        puts("Here's your 2 arguments:");

        int i;

        for (i = 1; i < argc; i += 1)
        {
            printf("%s ", argv[i]);
        }
        printf("\n");
    }
    else
    {
        printf("So many arguments I can't handle the truth\n");
    }

    return 0;
}

