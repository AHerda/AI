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
    srand(n);
    for(int x = 0; x < size; x++) {
        for(int y = 0; y < size; y++) {
            plane[x][y] = (x * 4 + y + 1) % 16;
        }
    }
    x = size - 1;
    y = size - 1;

    for(int i = 0; i < n; i++) {
        int r = rand() % 4;
        bool check;
        switch (r) {
            case 0:
                check = move('w');
                break;
            case 1:
                check = move('s');
                break;
            case 2:
                check = move('a');
                break;
            case 3:
                check = move('d');
                break;
            default:
                check = false;
        }

        if(!check)
            i--;
    }
}

bool Gra::move(char ch) {
    switch (ch)
    {
    case 'w':
    case 'W':
        if(y == 0)
            return false;
        plane[x][y] = plane[x][y - 1];
        plane[x][y - 1] = 0;
        y--;
        return true;
    case 's':
    case 'S':
        if(y == size - 1)
            return false;
        plane[x][y] = plane[x][y + 1];
        plane[x][y + 1] = 0;
        y++;
        return true;
    case 'a':
    case 'A':
        if(x == 0)
            return false;
        plane[x][y] = plane[x - 1][y];
        plane[x - 1][y] = 0;
        x--;
        return true;
    case 'd':
    case 'D':
        if(x == size - 1)
            return false;
        plane[x][y] = plane[x + 1][y];
        plane[x + 1][y] = 0;
        x++;
        return true;
    default:
        return false;
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