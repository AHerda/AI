#pragma once

#include <string.h>

int depth, bot;
int minmax(int board[5][5], int player, int move, int alpha, int beta);
int value(int board[5][5], int player);
int inertion(int board[5][5], int player);

int bestMove(int player) {
    bot = player;
    int best_move = 0;
    int max = -10000;
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
            if(board[i][j] == 0) {

                board[i][j] = player;
                int temp = minmax(board, 3 - bot, 1, -1000, 1000);
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
    if(move >= depth) return 0;
    else if(winCheck(player)) return (player == bot) ? 1000 : -1000;
    else if(loseCheck(player)) return (player == bot) ? -1000 : 1000;

    int best = (player == bot) ? -1000 : 1000;

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
    }

    if(!possible_move_check) return 0;
    return best;
}

int value(int board[5][5], int player) {
    return inertion(board, player);
}

int inertion(int board[5][5], int player) {
    int sum = 0;
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
            if(board[i][j] == player) {
                sum += std::abs(i - 3 + 1) + std::abs(j - 3 + 1);
            }
        }
    }
    return 200 - sum;
}