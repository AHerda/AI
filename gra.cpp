#include <iostream>
#include <vector>
#include <random>
#include "gra.hpp"

using namespace std;

Gra::Gra(int size) {
    this->size = size;
    for(int i = 0; i < size; i++) {
        vector<int> temp;
        temp.assign(size, 0);
        plane.push_back(temp);
    }
}

Gra::~Gra() {
    for(int i = 0; i < size; i++)
        plane[i].~vector();
    plane.~vector();
}

void Gra::rand_start() {

}

void Gra::rand_start_ez(int n) {
    srand(time(NULL));
    for(int x = 0; x < size; x++) {
        for(int y = 0; y < size; y++) {
            plane[x][y] = (x * size + y + 1) % (size * size);
        }
    }
    x = size - 1;
    y = size - 1;

    int i = 0;
    while(i != 100) {
        int r = rand() % 4;
        bool check;
        check = move(r);

        if(check)
            i++;
    }
}

bool Gra::move(int r) {
    switch (r)
    {
    case 0:
        if(x == 0)
            return false;
        plane[x][y] = plane[x - 1][y];
        plane[x - 1][y] = 0;
        x--;
        return true;
    case 1:
        if(x == size - 1)
            return false;
        plane[x][y] = plane[x + 1][y];
        plane[x + 1][y] = 0;
        x++;
        return true;
    case 2:
        if(y == 0)
            return false;
        plane[x][y] = plane[x][y - 1];
        plane[x][y - 1] = 0;
        y--;
        return true;
    case 3:
        if(y == size - 1)
            return false;
        plane[x][y] = plane[x][y + 1];
        plane[x][y + 1] = 0;
        y++;
        return true;
    default:
        return false;
    }
}

int translator(char ch) {
    switch (ch) {
        case 'w':
        case 'W':
            return 0;
        case 's':
        case 'S':
            return 1;
        case 'a':
        case 'A':
            return 2;
        case 'd':
        case 'D':
            return 3;
    }
    return -1;
}

bool Gra::check_win() {
    int counter = 0;

    for(int x = 0; x < size; x++) {
        for(int y = 0; y < size; y++) {
            if(plane[x][y] == x * 4 + y + 1) {
                counter++;
            }
            else if(x == this->x && y == this->y && x * 4 + y == 15) {
                counter++;
            }
        }
    }

    return counter == 16;
}

void Gra::print_table() {
    cout << "-----------------------------\n";
    for(int x = 0; x < size; x++) {
        for(int y = 0; y < size; y++) {
            cout << "| " << plane[x][y] << " ";
        }
        cout << "|\n";
        cout << "-----------------------------\n";
    }
}

int Gra::get(int x, int y) {
    return plane[x][y];
}

int Gra::get_size() {
    return size;
}

int Gra::get_xy() {
    return x * 4 + y;
}