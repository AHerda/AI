#include <unordered_map>
#include <vector>
#include <limits>
#include "a_star.hpp"
#include "gra.hpp"

using namespace std;

A_star::A_star(Gra& gra, int heurestic) {
    this->gra = gra;
    this->test = gra.get_board();
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
    int total = 0;
    for (int x = 0; x < gra.get_size(); x++) {
        for (int y = 0; y < gra.get_size(); y++) {
            int value = (gra.get(x, y) + 15) % 16;
            total += manhattan_dist(x, y, value / gra.get_size(), value % gra.get_size());
        }
    }
    return total;
}

int A_star::total_manhattan_1d(vector<int> board) {
    int total = 0;
    for (int x = 0; x < gra.get_size(); x++) {
        for (int y = 0; y < gra.get_size(); y++) {
            int value = board[x * gra.get_size() + y];
            if(value == 0) total += manhattan_dist(x, y, gra.get_size() - 1, gra.get_size() - 1);
            else total += manhattan_dist(x, y, (value - 1) / gra.get_size(), (value - 1) % gra.get_size());
        }
    }
    return total;
}

int A_star::heurestic1(vector<Node*>& to_visit) {
    int i = 0;
    int result = 0;
    int smallest_cost = std::numeric_limits<int>::max();
    for(Node* node : to_visit) {
        if(node->cost < smallest_cost) {
            int dist = total_manhattan_1d(node->state);

            if(dist + node->cost < smallest_cost) {
                smallest_cost = dist + node->cost;
                result = i;
            }
        }

        i++;
    }

    return result;
}

void A_star::A_star_search(const vector<vector<int>> board) {
    unordered_map<vector<int>, bool> visited;
    vector<Node*> to_visit;

    Node* start = new Node(gra.to_1d(), NONE, nullptr);

    visited.insert(pair<vector<int>, bool>(start->state, true));
    to_visit.push_back(start);

    Node* current = to_visit.front();

    while(true) {
        int i;
        if(heurestic == 0) {
            i = heurestic1(to_visit);
        }

        current = to_visit[i];

        vector<Node*> component;

        get_neighbors(current, component);
        for(Node* node : component) {
            to_visit.push_back(node);
        }

        if(current->check_win(gra))
            break;

        to_visit.erase(to_visit.begin() + i);
    }

    vector<int> path;
    while(current->parent)
}

void A_star::get_neighbors(Node* node, vector<Node*>& component) {
    int x, y;
    int temp = get_blank(node->state_2d);
    x = temp / 4;
    y = temp % 4;

    Node* temp2;
    if(x != 0) {
        component.push_back(node->move(UP, x, y));
    }
    if(x != gra.get_size()) {
        component.push_back(node->move(DOWN, x, y));
    }
    if(y != 0) {
        component.push_back(node->move(LEFT, x, y));
    }
    if(y != gra.get_size()) {
        component.push_back(node->move(RIGHT, x, y));
    }
}

int A_star::get_blank(vector<vector<int>> board) {
    for (int x = 0; x < gra.get_size(); x++) {
        for (int y = 0; y < gra.get_size(); y++) {
            if(board[x][y] == 0) {
                return x * gra.get_size() + y;
            }
        }
    }
    return -1;
}