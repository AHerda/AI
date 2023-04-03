#include <iostream>
#include "gra.hpp"
#include "a_star.hpp"

int main(int argc, char** argv) {
    Gra gra(4);
    gra.rand_start();
    gra.print_table();

    A_star as(gra);
    as.A_star_search();
    as.execute();

    cout << gra.check_win();
    gra.print_table();

    return 0;
}