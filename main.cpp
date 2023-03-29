#include <iostream>
#include "gra.hpp"
#include "a.hpp"

int main(int argc, char** argv) {
    Gra gra(4);
    gra.rand_start_ez(1000);
    gra.print_table();
    gra.~Gra();

    return 0;
}