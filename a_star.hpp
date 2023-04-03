#ifndef a_star_hpp
#define a_star_hpp

#include <fstream>
#include <vector>
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
    vector<vector<int>> state_2d;  // Obecny stan planszy
    Dir move;           // W którą stronę poszło puste pole aby stworzyć tego node
    int cost;          // Ilość wykonanych ruchów 
    Node* parent;

    Node(vector<int> state, Dir parent_move, Node* parent) {
        this->state = state;
        this->move = parent_move;
        this->parent = parent;
        this->cost = parent->cost + 1;

        to_2d();
    }

    Node(vector<vector<int>> state_2d, Dir parent_move, Node* parent) {
        this->state_2d = state_2d;
        this->move = parent_move;
        this->parent = parent;
        this->cost = parent->cost + 1;

        to_1d();
    }

    void to_1d() {
        int i = 0;
        for (int x = 0; x * x < state.size(); x++) {
            for (int y = 0; y * y < state.size(); y++) {
                state.push_back(state_2d[x][y]);
            }
        }
    }

    void to_2d() {
        int i = 0;
        for (int x = 0; x * x < state.size(); x++) {
            state_2d.push_back(vector<int>());
            for (int y = 0; y * y < state.size(); y++) {
                state_2d[x].push_back(state[x * i]);
                i++;
            }
        }
    }

    bool check_win(Gra &gra) {
        return gra.check_win();
    }

    bool is_visited(unordered_map<vector<int>, bool> &map) {
        auto temp = map.find(state);
        if(temp == map.end()) return false;

        return true;
    }

    Node* move(Dir dir, int x, int y) {
        vector<vector<int>> temp = state_2d;
        if(dir == UP && x != 0) {
            temp[x][y] = temp[x - 1][y];
            temp[x - 1][y] = 0;

            Node* temp2 = new Node(temp, UP, this);
            return temp2;
        }
        if(dir == DOWN && x + 1 != temp.size()) {
            temp = state_2d;

            temp[x][y] = temp[x + 1][y];
            temp[x + 1][y] = 0;

            Node* temp2 = new Node(temp, DOWN, this);
            return temp2;
        }
        if(dir == LEFT && y != 0) {
            temp = state_2d;

            temp[x][y] = temp[x][y - 1];
            temp[x][y - 1] = 0;

            Node* temp2 = new Node(temp, LEFT, this);
            return temp2;
        }
        if(dir == RIGHT && y + 1 != temp.size()) {
            temp = state_2d;

            temp[x][y] = temp[x][y + 1];
            temp[x][y + 1] = 0;

            Node* temp2 = new Node(temp, RIGHT, this);
            return temp2;
        }
        return nullptr;
    }
};

class A_star {
    private:

    Gra gra;
    vector<vector<int>> test;
    int heurestic;

    public:

    A_star(Gra &gra, int heurestic = 0);
    int manhattan_dist(int x1, int y1, int x2, int y2);
    int total_manhattan();
    int total_manhattan_1d(vector<int> board);
    int get_blank(vector<vector<int>> board);
    void get_neighbors(Node* node, vector<Node*>& component);
    

    void A_star_search(const vector<vector<int>> board);

    int heurestic1(vector<Node*>& to_visit);
};

#endif