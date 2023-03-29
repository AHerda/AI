#include <iostream>
#include <vector>
#include "gra.hpp"

using namespace std;

Gra::Gra(int size = 3) {
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

void Gra::move(char ch) {
    switch (ch)
    {
    case 'w':
        if(y == 0)
            break;
        plane[x][y] = plane[x][y - 1];
        plane[x][y - 1] = 0;
        y--;
        break;
    case 's':
        if(y == size - 1)
            break;
        plane[x][y] = plane[x][y + 1];
        plane[x][y + 1] = 0;
        y++;
        break;
    case 'a':
        if(x == 0)
            break;
        plane[x][y] = plane[x - 1][y];
        plane[x - 1][y] = 0;
        x--;
        break;
    case 'd':
        if(x == size - 1)
            break;
        plane[x][y] = plane[x + 1][y];
        plane[x + 1][y] = 0;
        x++;
        break;
    default:
        break;
    }
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
    for(vector<int> v : plane) {
        for(int val : v) {
            cout << "| " << val << " ";
        }
        cout << "|\n";
        cout << "-----------------------------\n";
    }
}

int Gra::get(int x, int y) {
    return plane[x][y];
}

int Gra::get_size() {
    return this->size;
}

int Gra::get_xy() {
    return (this->x) * 4 + (this->y);
}