#include <stdio.h>
#include "ex22.h"
#include "../dbg.h"

// this var is "extern'd" so it's visible in other .c files
int THE_SIZE = 1000;

// not "extern'd", but it's static (?) and we provide getter and setter...
// static in C: only used in this file
static int THE_AGE = 37;

int get_age()
{
    return THE_AGE;
}

void set_age(int age)
{
    THE_AGE = age;
}

// this is very interesting...
double update_ratio(double new_ratio)
{
    // same as regular static but scope limited to this function.
    // it behaves like it was declared like THE_AGE, only smaller scope
    static double ratio = 1.0;

    double old_ratio = ratio;
    ratio = new_ratio;

    return old_ratio;
}

// presumably, this will demonstrate some discrepancy between what
// we think the value of size is and what it actually is somewhere else...?
void print_size()
{
    log_info("I think size is: %d", THE_SIZE);
}
