/* stdlib includes */
#include <stdio.h>
#include <ctype.h>
#include <string.h>

/* forward declarations */
void print_letters(char str[]);

/* prints arguments passed to main() */
void print_arguments(int argc, char *argv[])
{
    int i;
    for (i = 0; i < argc; i += 1)
    {
        print_letters(argv[i]);
    }
}

/* print a string char by char */
void print_letters(char str[])
{
    int i;
    for (i = 0; i < strlen(str); i += 1)
    {
        char ch = str[i];
        if (isalpha(ch) || isblank(ch))
        {
            printf("'%c' == %d ", ch, ch);
        }
    }

    printf("\n");
}

int main(int argc, char *argv[])
{
    print_arguments(argc, argv);
    return 0;
}
