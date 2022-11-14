#include <iostream>

#include "helpers.h"

int main()
{
    START_TIMER(point_1)
    std::cout << "Hello, World!" << std::endl;

    STOP_TIMER(point_1)
    return 0;
}
