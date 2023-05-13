#pragma once

#include <string.h>

int depth, bot;
int minmax(int board[5][5], int player, int move, int alpha, int beta);

int bestMove(int player) {
    bot = player;
    int best_move = 0;
    int max = -10000;
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
            if(board[i][j] == 0) {

                board[i][j] = player;
                int temp = minmax(board, bot, 0, -100000, 100000);
                board[i][j] = 0;

                if(temp > max) {
                    max = temp;
                    best_move = i * 10 + j;
                }
            }
        }
    }

    return best_move + 11;
}



int minmax(int board[5][5], int player, int move, int alpha, int beta) {
    if(winCheck(player)) return (player == bot) ? 1000 : -1000;
    if(loseCheck(player)) return (player == bot) ? -1000 : 1000;
    if(move == depth) return 0;//value(board);

    int best = (player == bot) ? -10000 : 10000;

    bool possible_move_check = false;
    if(player == bot) {
        for(int i = 0; i < 5; i++) {
            for(int j = 0; j < 5; j++) {
                if(board[i][j] == 0) {
                    possible_move_check = true;

                    board[i][j] = player;
                    int temp = minmax(board, 3 - player, move + 1, alpha, beta);
                    board[i][j] = 0;

                    if(temp > best) {
                        best = temp - move * 10;

                        alpha = (alpha < best) ? best : alpha;
                        if(beta <= alpha) break;
                    }
                }
            }
        }
        if(!possible_move_check) return 0;
        return best;
    }
    else {
        for(int i = 0; i < 5; i++) {
            for(int j = 0; j < 5; j++) {
                if(board[i][j] == 0) {
                    possible_move_check = true;

                    board[i][j] = player;
                    int temp = minmax(board, 3 - player, move + 1, alpha, beta);
                    board[i][j] = 0;

                    if(temp < best) {
                        best = temp + move * 10;

                        beta = (beta > best) ? best : beta;
                        if(beta <= alpha) break;
                    }
                }
            }
        }
        if(!possible_move_check) return 0;
        return -1 * best;
    }
}

int value(int board[5][5]) {
    return 5;
}