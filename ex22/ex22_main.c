#include "ex22.h"
#include "../dbg.h"

const char *MY_NAME = "Zed A. Shaw";

void scope_demo(int count)
{
    log_info("count is: %d", count);

    if (count > 10)
    {
        int count = 100;
        log_info("count in this scope is %d", count);
    }

    log_info("count at exit is: %d", count);

    // because the param is an int, and not *int, I think this
    // will fail (the value outside this function will not change)
    count = 3000;

    log_info("count after assign: %d", count);
}

int main(int argc, char *argv[])
{
    // test getter/setter for age
    log_info("My name: %s, age: %d", MY_NAME, get_age());
    set_age(100);
    log_info("My age is now: %d", get_age());

    // test out size extern
    log_info("THE_SIZE is: %d", THE_SIZE);
    print_size();
    THE_SIZE = 9;
    log_info("THE_SIZE is now: %d", THE_SIZE);
    print_size();

    // test the ratio func static
    log_info("Ratio at first: %f", update_ratio(2.0));
    log_info("Ratio again: %f", update_ratio(10.0));
    log_info("Ratio once more: %f", update_ratio(300.0));

    // test scope_demo
    int count = 4;
    scope_demo(count);
    scope_demo(count * 20);
    log_info("count after calling scope_demo: %d", count);

    return 0;
}



