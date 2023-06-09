#ifndef a_star_hpp
#define a_star_hpp

#include <iostream>
#include <bits/stdc++.h>

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

    int neighbors(std::unordered_set<unsigned long long>& visited, std::vector<Node*>& to_visit, Node* current);
    void add_if_not_explored(std::unordered_set<unsigned long long>& visited, std::vector<Node*>& to_visit, Node* node, int &count);
    bool is_explored(std::unordered_set<unsigned long long>& visited, unsigned long long state);
    void add_explored(std::unordered_set<unsigned long long>& visited, unsigned long long state);
    

    void A_star_search();
    void execute();

    int heurestic1(std::vector<Node*> to_visit);
    int heurestic2(std::vector<Node*> to_visit);

    int rowConflicts(std::vector<int> tiles);
    int columnConflicts(std::vector<int> tiles);
    int linearConflicts(std::vector<int> tiles);
};

#endif