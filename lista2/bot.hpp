#pragma once

#include <string.h>

int depth;

int bestMove() {
    int best_move;
    int min;
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
            if(board[i][j] == 0) {
                int temp = cost(i, j, 0);
                if(temp < min) {
                    min = temp;
                    best_move = i * 10 + j;
                }
            }
        }
    }
    return best_move;
}

int cost(int i, int j, int move, int minmizing) {

}