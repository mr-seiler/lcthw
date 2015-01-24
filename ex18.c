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

// function pointer type for integer sorting function that will sort
// the numbers in-place.
typedef void (*sort_cb)(int *numbers, int count, compare_cb cmp);

/* Swaps two numbers in an integer array. */
void swap(int *numbers, int idx1, int idx2)
{
    int temp = numbers[idx1];
    numbers[idx1] = numbers[idx2];
    numbers[idx2] = temp;
}

/* Given an array of numbers, sorting function, and a comparison function,
 * returns a pointer to a sorted copy of the array on the heap.
 */
int *do_sort(int *numbers, int count, sort_cb sorter, compare_cb cmp)
{
    int *target = malloc(count * sizeof(int));
    if (!target) die("Memory error");

    memcpy(target, numbers, count * sizeof(int));

    sorter(target, count, cmp);
    return target;
}

/* Implements sort_cb:
 * Given a pointer to some numbers, the number of numbers,
 * and a comparison function, sorts the numbers in-place using insertion sort.
 */
void insertion_sort(int *numbers, int count, compare_cb cmp)
{
    int i, j;

    for (i = 1; i < count; i += 1)
    {
        j = i;
        while (j > 0 && (cmp(numbers[j - 1], numbers[j]) > 0))
        {
            swap(numbers, j, j - 1);
            j -= 1;
        }
    }
}

/* Implements sort_cb:
 * Given a pointer to some numbers, the number of numbers, and a
 * comparison function, sorts the numbers in-place using bubble sort.
 */
void bubble_sort(int *numbers, int count, compare_cb cmp)
{
    int i, j;

    for (i = 0; i < count; i += 1)
    {
        for (j = 0; j < count - 1; j += 1)
        {
            if (cmp(numbers[j], numbers[j+1]) > 0)
            {
                swap(numbers, j, j + 1);
            }
        }
    }
}

/* Implements compare_cb (forward/ascending order) */
int sorted_order(int a, int b)
{
    return a - b;
}

/* Implements compare_cb for reverse sorted order */
int reverse_order(int a, int b)
{
    return b - a;
}

/* Implements comapre_cb... for some other order. */
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

void print_ints(int *numbers, int count)
{
    int i;
    printf("[ ");
    for (i = 0; i < count; i += 1)
    {
        printf((i < count - 1 ? "%d, " : "%d") , numbers[i]);
    }
    printf(" ]\n");
}

void test_sorting(int *numbers, int count, sort_cb sorter, compare_cb cmp)
{
    int *sorted = do_sort(numbers, count, sorter, cmp);
    if (!sorted) die("Sort failed");

    // output the sorted array
    print_ints(sorted, count);

    // deallocate the sorted copy
    free(sorted);
}

/* Simple extension of rand() function that only returns numbers
 * in the range [0, ceil).  This method will break down as ceil
 * approaches RAND_MAX. More robust solutions can be found here:
 * http://c-faq.com/lib/randrange/html
 * http://stackoverflow.com/a/6852396
 */
int rand_ceil(int ceil)
{
    return rand() / (RAND_MAX / ceil + 1);
}

/* Returns a pointer to an array of size `count` on the heap, where
 * each int is initialized to a random number in the range 0..99
 */
int *get_random(int count)
{
    int i;
    int *numbers = malloc(count * sizeof(int));

    for (i = 0; i < count; i += 1)
    {
        numbers[i] = rand_ceil(100);
    }

    return numbers;
}

int main(int argc, char *argv[])
{
    // must be given at least one number argument
    if (argc < 2) die("USAGE: ./ex18 count");

    // try to get command line argument as #numbers
    int count = atoi(argv[1]);

    // get some random numbers, and print them out
    int *numbers = get_random(count);
    printf("Initial:\n");
    print_ints(numbers, count);

    // test bubble sort w/ different comparison functions
    puts("Bubble sort:");
    test_sorting(numbers, count, bubble_sort, sorted_order);
    test_sorting(numbers, count, bubble_sort, reverse_order);
    test_sorting(numbers, count, bubble_sort, strange_order);

    // test insertion sort w/ different comparison functions
    puts("Insertion sort:");
    test_sorting(numbers, count, insertion_sort, sorted_order);
    test_sorting(numbers, count, insertion_sort, reverse_order);
    test_sorting(numbers, count, insertion_sort, strange_order);

    // free heap
    free(numbers);

    return 0;
}
