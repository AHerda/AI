#include <iostream>
#include "gra.hpp"
#include "a_star.hpp"

int main(int argc, char** argv) {
    Gra gra(3);
    gra.rand_start_ez();
    gra.print_table();

    A_star as(gra);
    as.A_star_search();
    as.execute();

    gra.print_table();

    return 0;
}