#ifndef a_star_hpp
#define a_star_hpp

#include <iostream>
#include <set>
#include <vector>
#include <limits>
#include <string>
#include "gra.hpp"
#include "node.hpp"

class A_star {
    private:

    Gra gra;
    int heurestic;
    std::vector<Dir> path;

    public:

    A_star(Gra& gra, int heurestic = 0);
    int manhattan_dist(int x1, int y1, int x2, int y2);
    int total_manhattan(std::vector<int> board);

    int neighbors(std::set<std::string>& visited, std::vector<Node*>& to_visit, Node* current);
    void add_if_not_explored(std::set<std::string>& visited, std::vector<Node*>& to_visit, Node* node, int &count);
    bool is_explored(std::set<std::string>& visited, std::string state);
    void add_explored(std::set<std::string>& visited, std::string state);
    

    void A_star_search();
    void execute();

    int heurestic1(std::vector<Node*> to_visit);
};

#endif