#ifndef _ex22_h
#define _ex22_h

// extern allows a variable in a .c file to be accessed from other .c files
extern int THE_SIZE;

// getter and setter for an "internal static" variable in ex22.c
int get_age();
void set_age(int age);

// updates a static variable that's inside update_ratio
// (fascinating... a function with persistent state!)
double update_ratio(double ratio);

void print_size();

#endif
