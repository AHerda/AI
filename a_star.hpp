#ifndef a_star_hpp
#define a_star_hpp

#include <fstream>
#include "gra.hpp"

enum Dir {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NONE
};

class Node {
    public:

    vector<int> state;  // Obecny stan planszy
    Dir move;           // W którą stronę poszło puste pole aby stworzyć tego node
    int cost;          // Ilość wykonanych ruchów 
    Node* parent;

    Node(vector<int> state, Dir parent_move, Node* parent) {
        this->state = state;
        this->move = parent_move;
        this->parent = parent;
        this->cost = parent->cost + 1;
    }

    bool check_win(Gra& gra) {
        return gra.check_win();
    }

    bool is_visited(unordered_map<vector<int>, bool> &map) {
        auto temp = map.find(state);
        if(temp == map.end()) return false;

        return true;
    }
};

class A_star {
    private:

    Gra gra;
    vector<vector<int>> test;
    int heurestic;

    public:

    A_star(Gra& gra, int heurestic = 0);
    int manhattan_dist(int x1, int y1, int x2, int y2);
    int total_manhattan();

    void A_star_search(const vector<vector<int>> board);
};

#endif