#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include "gra.hpp"


Gra::Gra(int size) {
    this->size = size;
    board = std::vector<int>(size);
}

void Gra::rand_start_ez(int n) {
    std::mt19937 mt(std::random_device{}()); 
    for(int i = 0; i < size * size; i++) {
        board[i] = (i + 1) % (size * size);
    }
    x = size - 1;
    y = size - 1;
    blank = size * size - 1;

    int i = 0;
    while(i < n) {
        int r = mt() % 4;
        bool check;
        check = move(translator_int(r));

        if(check)
            i++;
    }
}

void Gra::rand_start() {
    std::vector<int> temp;
    for(int i = 0; i  < size * size; i++) {
        temp.push_back((i + 1) % (size * size));
    }

    std::default_random_engine dre(std::random_device{}());
    do {
        shuffle(temp.begin(), temp.end(), dre);
    } while(!solvable(temp));

    board = temp;
}

bool Gra::solvable(std::vector<int> tab) {
    int inversions_count = 0;
    for (int i = 0; i < size * size - 1; i++) {
        for (int j = i + 1; j < size * size; j++) {
            if (tab[i] > tab[j] && tab[i] != 0 && tab[j] != 0) {
                inversions_count++;
            }
        }
    }
    if (inversions_count % 2 == 0) {
        return true;
    }
    return false;
}

bool Gra::move(Dir d) {
    bool check = false;
    int index;
    for(int i = 0; i < size * size; i++) {
        if(board[i] == 0) {
            index = i;
        }
    }

    switch (d) {
        case UP:
            if(index >= size) {
                board[index] = board[index - size];
                board[index - size] = 0;
                blank = index - size;
                x--;
                check = true;
            }
            break;
        case DOWN:
            if(index < size * (size - 1)) {
                board[index] = board[index + size];
                board[index + size] = 0;
                blank = index + size;
                x++;
                check = true;
            }
            break;
        case LEFT:
            if(index % size != 0) {
                board[index] = board[index - 1];
                board[index - 1] = 0;
                blank = index - 1;
                y--;
                check = true;
            }
            break;
        case RIGHT:
            if(index % size != size - 1) {
                board[index] = board[index + 1];
                board[index + 1] = 0;
                blank = index + 1;
                y++;
                check = true;
            }
            break;
        case NONE:
            check = true;
            break;
    }
    if(check_win()) {
        std::cout << "============" << std::endl << "Wygrana!!!!!" << std::endl << "============" << std::endl;
        print_table();
    }
    return check;
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

    for(int i = 0; i < size * size; i++) {
        if(board[i] == (i + 1) % (size * size)) counter++;
    }

    return counter == size * size;
}

void Gra::print_table() {
        std::cout << "-----------------------------\n";
        int i = 0;
        for(int x = 0; x < size; x++) {
            for(int y = 0; y < size; y++) {
                std::cout << "| " << board[i] << " ";
                i++;
            }
            std::cout << "|\n";
            std::cout << "-----------------------------\n";
        }
    }

int Gra::get(int x, int y) {
    return board[x * size + y];
}

int Gra::get_size() {
    return size;
}

int Gra::get_xy() {
    return blank;
}

std::vector<int> Gra::get_board() {
    return board;
}