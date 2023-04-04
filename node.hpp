#ifndef node_hpp
#define node_hpp

#include <iostream>
#include <vector>
#include <string>
#include "Dir.hpp"


class Node {
    public:

    Node* parent;
    std::vector<int> state;  // Obecny stan planszy
    Dir move;           // W którą stronę poszło puste pole aby stworzyć tego node
    int cost;          // Ilość wykonanych ruchów 


    Node(std::vector<int> state, Dir parent_move, Node* parent, int cost) {
        this->state = state;
        this->move = parent_move;
        this->parent = parent;
        this->cost = cost;
    }

    std::string state_to_string() {
        std::string result;
        for(size_t i = 0; i < state.size(); i++) {
            result += std::to_string(state[i]);
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

    void print_table2() {
        std::cout << "-----------------------------\n";
        int i = 0;
        for(int x = 0; x * x < state.size(); x++) {
            for(int y = 0; y * y < state.size(); y++) {
                std::cout << "| " << state[i] << " ";
                i++;
            }
            std::cout << "|\n";
            std::cout << "-----------------------------\n";
        }
    }
};

#endif