#ifndef gra_hpp
#define gra_hpp

#include <vector>

using namespace std;

class Gra {
    private:

    int size;           //wielkość planszy
    int x, y;           //miejsce puste
    vector<vector<int>> plane;  //plansza wielkości size

    public:

    Gra(int size = 3);
    ~Gra();
    void rand_start();
    void rand_start_ez(int n = 100);
    bool move(int r);
    int translator(char ch);
    bool check_win();
    int get_size();
    int get_xy();
    int get(int x, int y);
    void print_table();
};

#endif