#pragma once

#include <stdlib.h>
#include <iostream>
#include <set>

int depth, bot;
std::set<long long> set;
int minmax(int board[5][5], int player, int move, int alpha, int beta);
int value(int board[5][5], int player);
int inertion(int board[5][5], int player);
bool visited(int board[5][5]);
long long boardToInt(int board[5][5]);

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
    if(visited(board)) return -1000;
    if(winCheck(player)) return (player == bot) ? 1000 : -1000;
    if(loseCheck(player)) return (player == bot) ? -1000 : 1000;
    if(move == depth) return (player == bot) ? value(board, player) : -1 * value(board, player);

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

int value(int board[5][5], int player) {
    return inertion(board, player);
}

int inertion(int board[5][5], int player) {
    int sum = 0;
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
            if(board[i][j] == player) {
                sum += abs(i - 3 + 1) + abs(j - 3 + 1);
            }
        }
    }
    return 200 - sum;
}

bool visited(int board[5][5]) {
    return set.insert(boardToInt(board)).second;
}

long long boardToInt(int board[5][5]) {
    long long result = 0;
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
            result += board[i][j];

            if(i != 4 || j != 4) {
                result << 2;
            }
        }
    }

    return result;
}