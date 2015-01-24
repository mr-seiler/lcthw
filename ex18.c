#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

void die(const char *message)
{
    if (errno)
    {
        perror(message);
    }
    else
    {
        printf("ERROR: %s\n", message);
    }
    exit(1);
}

// function pointer type for a function that takes to ints and returns one
typedef int (*compare_cb)(int a, int b);


// does this need to take a pointer to some ints, or a pointer to a pointer?
// ...apparently this is fine (it works ok);
void swap(int *numbers, int idx1, int idx2)
{
    int temp = numbers[idx1];
    numbers[idx1] = numbers[idx2];
    numbers[idx2] = temp;
}

/* Given a a pointer to a number (which we can use like an array)
 * and a number of ints (length of the array) and a comparison
 * fucntion pointer, sort the numbers really inefficiently.
 * Return type of int* can either point to sorted array of ints
 * or just one int (like if there was an error)
 */
int *bubble_sort(int *numbers, int count, compare_cb cmp)
{
    int i = 0, j = 0;

    // allocate enough memory for the sorted version of the array
    int *target = malloc(count * sizeof(int));
    if (!target) die("Memory error");

    // copy the original array to the new location, which we will sort in-place
    memcpy(target, numbers, count * sizeof(int));

    // do bubble sort of new array copy
    for (i = 0; i < count; i += 1)
    {
        for (j = 0; j < count - 1; j += 1)
        {
            if (cmp(target[j], target[j+1]) > 0)
            {
                // do swap
                swap(target, j, j + 1);
            }
        }
    }

    return target;
}

/* define a compare function for forward sorted order */
int sorted_order(int a, int b)
{
    return a - b;
}

/* define a compare function for reverse sorted order */
int reverse_order(int a, int b)
{
    return b - a;
}

/* yet another compare function.  Is "strange order" actually a thing? */
int strange_order(int a, int b)
{
    if (a == 0 || b == 0)
    {
        return 0;
    }
    else
    {
        return a % b;
    }
}

void test_sorting(int *numbers, int count, compare_cb cmp)
{
    int i;
    int *sorted = bubble_sort(numbers, count, cmp);

    if (!sorted) die("Sort failed");

    for (i = 0; i < count; i += 1)
    {
        printf("%d ", sorted[i]);
    }
    printf("\n");

    // deallocate the sorted copy
    free(sorted);
}

int main(int argc, char *argv[])
{
    // must be given at least one number argument
    if (argc < 2) die("USAGE: ./ex18 4 3 1 4 6");

    // count of numbers
    int count = argc - 1;
    int i;
    // pointer to the first real argument in arg array
    char **inputs = argv + 1;

    // allocate enough heap for the list of input numbers
    int *numbers = malloc(count * sizeof(int));
    if (!numbers) die("Memory error");

    // create int array from string arguments
    for (i = 0; i < count; i += 1)
    {
        numbers[i] = atoi(inputs[i]);
    }

    // test w/ different comparison functions
    test_sorting(numbers, count, sorted_order);
    test_sorting(numbers, count, reverse_order);
    test_sorting(numbers, count, strange_order);

    // free heap
    free(numbers);

    return 0;
}
