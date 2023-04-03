#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include "gra.hpp"

using namespace std;

Gra::Gra(int size) {
    this->size = size;
    board = vector<vector<int>>(size, vector<int>(size));
}

void Gra::rand_start_ez(int n) {
    mt19937 mt(random_device{}()); 
    for(int x = 0; x < size; x++) {
        for(int y = 0; y < size; y++) {
            board[x][y] = (x * size + y + 1) % (size * size);
        }
    }
    x = size - 1;
    y = size - 1;

    int i = 0;
    while(i != n) {
        int r = mt() % 4;
        bool check;
        check = move(translator_int(r));

        if(check)
            i++;
    }
}

void Gra::rand_start() {
    vector<int> temp = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0};
    default_random_engine dre(random_device{}());
    do {
        shuffle(temp.begin(), temp.end(), dre);
    } while(!solvable(temp));

    for(int x = 0; x < size; x++) {
        for(int y = 0; y < size; y++) {
            board[x][y] = temp[x * size + y];
        }
    }
}

bool Gra::solvable(vector<int> tab) {
    int parity = 0;
    int grid_width = size;
    int row = 0;        // obecny rząd
    int blank_row = 0;   // rząd z pustym polem

    for (size_t i = 0; i < tab.size(); i++)
    {
        if (i % grid_width == 0) {
            row++;
        }
        if (tab[i] == 0) {
            blank_row = row;
            continue;
        }
        for (size_t j = i + 1; j < tab.size(); j++)
        {
            if (tab[i] > tab[j] && tab[j] != 0)
            {
                parity++;
            }
        }
    }

    if (grid_width % 2 == 0) {
        if (blank_row % 2 == 0) {
            return parity % 2 == 0;
        } 
        else {
            return parity % 2 != 0;
        }
    } 
    else {
        return parity % 2 == 0;
    }
}

bool Gra::move(Dir d) {
    switch (d) {
        case UP:
            if(x == 0)
                return false;
            board[x][y] = board[x - 1][y];
            board[x - 1][y] = 0;
            x--;
            return true;
        case DOWN:
            if(x == size - 1)
                return false;
            board[x][y] = board[x + 1][y];
            board[x + 1][y] = 0;
            x++;
            return true;
        case LEFT:
            if(y == 0)
                return false;
            board[x][y] = board[x][y - 1];
            board[x][y - 1] = 0;
            y--;
            return true;
        case RIGHT:
            if(y == size - 1)
                return false;
            board[x][y] = board[x][y + 1];
            board[x][y + 1] = 0;
            y++;
            return true;
        case NONE:
            bool check = check_win();
            if(check) {
                cout << "Wygrana!!!";
            }
            else {
                cout << "Może następnym razem :((";
            }
            return true;
    }
    return false;
}

Dir Gra::translator_char(char ch) {
    switch (ch) {
        case 'w':
        case 'W':
            return UP;
        case 's':
        case 'S':
            return DOWN;
        case 'a':
        case 'A':
            return LEFT;
        case 'd':
        case 'D':
            return RIGHT;
    }
    return NONE;
}

Dir Gra::translator_int(int r) {
    switch (r) {
        case 0:
            return UP;
        case 1:
            return DOWN;
        case 2:
            return LEFT;
        case 3:
            return RIGHT;
    }
    return NONE;
}

bool Gra::check_win() {
    int counter = 0;

    for(int x = 0; x < size; x++) {
        for(int y = 0; y < size; y++) {
            if(board[x][y] == (x * 4 + y + 1) % (size * size)) {
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
            cout << "| " << board[x][y] << " ";
        }
        cout << "|\n";
        cout << "-----------------------------\n";
    }
}

int Gra::get(int x, int y) {
    return board[x][y];
}

int Gra::get_size() {
    return size;
}

int Gra::get_xy() {
    return x * 4 + y;
}

vector<int> Gra::to_1d() {
    vector<int> result;
    for(int x = 0; x < size; x++) {
        for(int y = 0; y < size; y++) {
            result.push_back(board[x][y]);
        }
    }
    return result;
}

vector<vector<int>> Gra::get_board() {
    vector<vector<int>> result(size, vector<int>(size));
    for(int x = 0; x < size; x++) {
        for(int y = 0; y < size; y++) {
            result[x][y] = board[x][y];
        }
    }
    return result;
}