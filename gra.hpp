#ifndef gra_hpp
#define gra_hpp

#include <vector>
#include "a_star.hpp"

using namespace std;

class Gra {
    private:

    int size;           //wielkość planszy
    int x, y;           //miejsce puste
    vector<vector<int>> board;  //plansza wielkości size

    public:

    Gra(int size = 3);
    void rand_start();
    void rand_start_ez(int n = 100);
    bool move(Dir d);
    Dir translator_char(char ch);
    Dir translator_int(int r);
    bool solvable(vector<int> tab);
    bool check_win();
    int get_size();
    int get_xy();
    int get(int x, int y);
    vector<vector<int>> get_board();
    void print_table();

    vector<int> to_1d();
};

#endif