#include <iostream>
#include "gra.hpp"
#include "a.hpp"

int main(int argc, char** argv) {
    Gra gra(5);
    gra.rand_start_ez();
    gra.print_table();

    return 0;
}