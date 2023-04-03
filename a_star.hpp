#ifndef a_star_hpp
#define a_star_hpp

#include <vector>
#include <string>
#include "gra.hpp"
#include "dir.hpp"

using namespace std;

class Node {
    public:

    vector<int> state;  // Obecny stan planszy
    vector<vector<int>> state_2d;  // Obecny stan planszy
    Dir move;           // W którą stronę poszło puste pole aby stworzyć tego node
    int cost;          // Ilość wykonanych ruchów 
    Node* parent;

    Node() {

    }

    Node(vector<int> state, Dir parent_move, Node* parent) {
        this->state = state;
        this->move = parent_move;
        this->parent = parent;
        if(parent != nullptr)
            this->cost = parent->cost + 1;

        to_2d();
    }

    Node(vector<vector<int>> state_2d, Dir parent_move, Node* parent) {
        this->state_2d = state_2d;
        this->move = parent_move;
        this->parent = parent;
        if(parent != nullptr)
            this->cost = parent->cost + 1;

        vector<int> temp(state_2d.size());
        to_1d();
    }

    void to_1d() {
        for (int x = 0; x * x < state_2d.size(); x++) {
            for (int y = 0; y * y < state_2d.size(); y++) {
                state[x * state_2d.size() + y] = state_2d[x][y];
            }
        }
    }

    void to_2d() {
        int i = 0;
        for (int x = 0; x * x < state.size(); x++) {
            i = x;
        }
        vector<vector<int>> temp(i, vector<int>(i));
        state_2d = temp;
        for (int x = 0; x < i; x++) {
            for (int y = 0; y < i; y++) {
                state_2d[x][y] = state[x * i + y];
            }
        }
    }

    string state_to_string() {
        string result;
        for(size_t i = 0; i < state.size(); i++) {
            result += to_string(state[i]);
            if(i + 1 != state.size()) {
                result += " ";
            }
        }
        return result;
    }

    bool check_win() {
        int counter = 0;

        for(size_t i = 0; i < state.size(); i++) {
            if(state[i] == (i + 1) % state.size()) counter++;
        }
        return counter == state.size();
    }

    Node* do_move(Dir dir, int x, int y) {
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
    vector<Dir> path;

    public:

    A_star(Gra& gra, int heurestic = 0);
    int manhattan_dist(int x1, int y1, int x2, int y2);
    int total_manhattan(vector<vector<int>> board);
    int total_manhattan_1d(vector<int> board);
    int get_blank(vector<vector<int>> board);
    void get_neighbors(Node* node, vector<Node*>& component);
    

    void A_star_search();
    void execute();

    int heurestic1(vector<Node*> to_visit);
};

#endif