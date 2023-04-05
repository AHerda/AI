#include "a_star.hpp"

A_star::A_star(Gra& gra, int heurestic) {
    this->gra = gra;
    this->heurestic = heurestic;
}

int A_star::manhattan_dist(int x1, int y1, int x2, int y2) {
    return abs(x2 - x1) + abs(y2 - y1);
}

int A_star::total_manhattan(std::vector<int> current) {
    int total = 0;
    for(int i = 0; i < current.size(); i++) {
        int value = current[i];
        if(value == 0) total += manhattan_dist(i / gra.get_size(), i % gra.get_size(), gra.get_size() - 1, gra.get_size() - 1);
        else total += manhattan_dist(i / gra.get_size(), i % gra.get_size(), (value - 1) / gra.get_size(), (value - 1) % gra.get_size());
    }
    return total;
}

int A_star::heurestic1(std::vector<Node*> to_visit) {
    int result = 0;
    int smallest_cost = std::numeric_limits<int>::max();
    for(int i = 0; i < to_visit.size(); i++) {
        if(to_visit[i]->cost < smallest_cost) {
            int dist = total_manhattan(to_visit[i]->state);

            if(dist + to_visit[i]->cost < smallest_cost) {
                smallest_cost = dist + to_visit[i]->cost;
                result = i;
            }
        }
    }
    return result;
}

int A_star::heurestic2(std::vector<Node*> to_visit) {
    int result = 0;
    int smallest_cost = std::numeric_limits<int>::max();
    for(int i = 0; i < to_visit.size(); i++) {
        if(to_visit[i]->cost < smallest_cost) {
            int dist = total_manhattan(to_visit[i]->state);
            int linear = linearConflicts(to_visit[i]->state);

            if(dist + linear + to_visit[i]->cost < smallest_cost) {
                smallest_cost = dist + to_visit[i]->cost;
                result = i;
            }
        }
    }
    return result;
}

void A_star::A_star_search() {
    int explored = 0;
    int max_nodes = 0;
    int new_nodes = 0;
    std::unordered_set<unsigned long long> visited;
    std::vector<Node*> to_visit;

    Node* start = new Node(gra.get_board(), NONE, nullptr, 0);

    add_explored(visited, start->state_to_ull());

    to_visit.push_back(start);

    Node* current = to_visit.front();

    while(to_visit.size() > 0) {
        int i;
        if(heurestic == 0) i = heurestic1(to_visit);
        else i = heurestic2(to_visit);

        current = to_visit[i];

        new_nodes = neighbors(visited, to_visit, current);
        explored++;
        max_nodes += new_nodes;

        if(current->check_win()) {
            std::cout << "znaleziono droge" << std::endl;
            break;
        }

        to_visit.erase(to_visit.begin() + i);
    }

    std::cout << "\nIlość ruchów w rozwiązaniu: " << current->cost;
    std::cout << "\nIlość sprawdzonych stanów: " << explored + 1;
    std::cout << "\nIlość stanów trzymana w pamięci: " << max_nodes + 1 << std::endl;



    while(current->parent) {
        path.push_back(current->move);
        current = current->parent;
    }
}

int A_star::neighbors(std::unordered_set<unsigned long long>& visited, std::vector<Node*>& to_visit, Node* current) {
    int index;
    for(int i = 0; i < gra.get_size() * gra.get_size(); i++) {
        if(current->state[i] == 0) {
            index = i;
        }
    }
    int exploredCount = 0;

    //UP
    if (!(index < gra.get_size())) {
        Node* node = new Node(current->state, Dir::UP, current, current->cost + 1);

        node->state[index] = node->state[index - gra.get_size()];
        node->state[index - gra.get_size()] = 0;

        add_if_not_explored(visited, to_visit, node, exploredCount);
    }

    //DOWN
    if (!(index >= gra.get_size() * (gra.get_size() - 1))) {
        Node* node = new Node(current->state, Dir::DOWN, current, current->cost + 1);

        node->state[index] = node->state[index + gra.get_size()];
        node->state[index + gra.get_size()] = 0;

        add_if_not_explored(visited, to_visit, node, exploredCount);
    }

    //LEFT
    if (!(index % gra.get_size() == 0)) {
        Node* node = new Node(current->state, Dir::LEFT, current, current->cost + 1);

        node->state[index] = node->state[index - 1];
        node->state[index - 1] = 0;

        add_if_not_explored(visited, to_visit, node, exploredCount);
    }

    //RIGHT
    if (!(index % gra.get_size() == gra.get_size() - 1)) {
        Node* node = new Node(current->state, Dir::RIGHT, current, current->cost + 1);

        node->state[index] = node->state[index + 1];
        node->state[index + 1] = 0;

        add_if_not_explored(visited, to_visit, node, exploredCount);
    }
    return exploredCount;
}

void A_star::add_if_not_explored(std::unordered_set<unsigned long long>& visited, std::vector<Node*>& to_visit, Node* node, int &count) {
    if (is_explored(visited, node->state_to_ull())) {
        delete node;
    }
    else {
        to_visit.push_back(node);
        add_explored(visited, node->state_to_ull());
        count++;
    }
}

bool A_star::is_explored(std::unordered_set<unsigned long long>& visited, unsigned long long state) {
    auto iterator = visited.find(state);
    if (iterator == visited.end()) {
        return false;
    }
    return true;
}

void A_star::add_explored(std::unordered_set<unsigned long long>& visited, unsigned long long state) {
    visited.insert(state);
}


void A_star::execute() {
    for(int i = path.size(); i >= 0; i--) {
        gra.move(path[i]);
        //if(i == 0) gra.print_table();
        //std::cout << path[i] << std::endl;
    }
}

int A_star::rowConflicts(std::vector<int> tiles) {
    int grid[gra.get_size()][gra.get_size()];
    int rowConflicts = 0;
    for (int i = 0; i < gra.get_size(); i++) {
        for (int j = 0; j < gra.get_size(); j++) {
            grid[i][j] = tiles[gra.get_size() * i + j];
        }
    }
    for (int i = 0; i < gra.get_size(); i++) {
        for (int j = 0; j < gra.get_size() - 1; j++) {
            if (grid[i][j] > grid[i][j + 1] && (grid[i][j] - 1) / gra.get_size() == i && (grid[i][j + 1] - 1) / gra.get_size() == i) {
                rowConflicts++;
            }
        }
    }

    return rowConflicts;
}

int A_star::columnConflicts(std::vector<int> tiles) {
    int grid[gra.get_size()][gra.get_size()];
    int columnConflicts = 0;
    for (int i = 0; i < gra.get_size(); i++) {
        for (int j = 0; j < gra.get_size(); j++) {
            grid[i][j] = tiles[gra.get_size() * i + j];
        }
    }
    for (int i = 0; i < gra.get_size() - 1; i++) {
        for (int j = 0; j < gra.get_size(); j++) {
            if (grid[i][j] > grid[i + 1][j] && (grid[i][j] - 1) % gra.get_size() == i && (grid[i + 1][j] - 1) % gra.get_size() == i) {
                columnConflicts++;
            }
        }
    }

    return columnConflicts;
}

int A_star::linearConflicts(std::vector<int> tiles) {
    int rowConflictsCount = rowConflicts(tiles);
    int columnConflictsCount = columnConflicts(tiles);

    return rowConflictsCount + columnConflictsCount;
}