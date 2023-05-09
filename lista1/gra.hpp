#ifndef gra_hpp
#define gra_hpp

#include <vector>
#include "dir.hpp"


class Gra {
    private:

    int size;           //wielkość planszy
    int x, y;           //miejsce puste
    int blank;          //miejsce puste ale 1D
    std::vector<int> board;  //plansza wielkości size

    public:

    Gra(int size = 3);
    void rand_start();
    void rand_start_ez(int n = 100);
    bool move(Dir d, bool check2 = false);
    Dir translator_char(char ch);
    Dir translator_int(int r);
    bool solvable(std::vector<int> tab);
    bool check_win();
    int get_size();
    int get_xy();
    int get(int x, int y);
    std::vector<int> get_board();
    void print_table();
};

#endif