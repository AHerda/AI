#include <unordered_map>
#include <string>
#include <vector>
#include "a_star.hpp"
#include "gra.hpp"

using namespace std;

A_star::A_star(Gra& gra, int heurestic) {
    this->gra = gra;
    this->heurestic = heurestic;
    for(int x = 0; x < gra.get_size(); x++) {
        for(int y = 0; y < gra.get_size(); y++) {
            this->test[x][y] = gra.get(x, y);
        }
    }
}

int A_star::manhattan_dist(int x1, int y1, int x2, int y2) {
    return abs(x2 - x1) + abs(y2 - y1);
}

int A_star::total_manhattan() {
    int total = 0; // total Manhattan distance of all tiles to their original locations
    for (int x = 0; x < gra.get_size(); x++) {
        for (int y = 0; y < gra.get_size(); y++) {
            int value = (gra.get(x, y) + 15) % 16;
            total += manhattan_dist(x, y, value / gra.get_size(), value % gra.get_size());
        }
    }
    return total;
}

void A_star::A_star_search(const vector<vector<int>> board) {
    unordered_map<vector<int>, bool> visited;

    Node start(gra.to_1d(), NONE, nullptr);
}

void get_neighbors()