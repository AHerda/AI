#include <vector>

using namespace std;

class Gra {
    private:

    int size;           //wielkość planszy
    int x, y;           //miejsce puste

    public:

    vector<vector<int>> plane;  //plansza wielkości size

    Gra(int size);
    ~Gra();
    void move(char ch);
    bool check_win();
    int get_size();
    int get_xy();
    void print_table();
};