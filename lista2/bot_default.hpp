#pragma once

#include <stdlib.h>
#include <iostream>

int depth, bot;


int minmax(int board[5][5], int player, int move, int alpha, int beta);
int value(int board[5][5], int player);
int heuristic(int board[5][5], int player);

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
    int best = value(board, player);
    if(move >= depth) return (player == bot) ? best : -best;
    else if(winCheck(player)) return (player == bot) ? 1000 : -1000;
    else if(loseCheck(player)) return (player == bot) ? -1000 : 1000;

    bool possible_move_check = false;
    if(player == bot) {
        best = -1000;
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
                        if(beta <= alpha) return alpha;
                    }
                }
            }
        }
    }
    else {
        best = 1000;
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
                        if(beta <= alpha) return beta;
                    }
                }
            }
        }
    }

    if(!possible_move_check) return 0;
    return best;
}

int value(int board[5][5], int player) {
    return heuristic(board, player) - heuristic(board, 3 - player);
}

int heuristic(int board[5][5], int player) {
    int result = 0;
    for(int i=0; i<28; i++)
        if(((board[win[i][0][0]][win[i][0][1]] == player) && (board[win[i][1][0]][win[i][1][1]] == 0) && (board[win[i][2][0]][win[i][2][1]] == player) && (board[win[i][3][0]][win[i][3][1]] == player))
        || ((board[win[i][0][0]][win[i][0][1]] == player) && (board[win[i][1][0]][win[i][1][1]] == player) && (board[win[i][2][0]][win[i][2][1]] == 0) && (board[win[i][3][0]][win[i][3][1]] == player)))
            result += 15;
        else if(((board[win[i][0][0]][win[i][0][1]] == player) && (board[win[i][1][0]][win[i][1][1]] == player) && (board[win[i][2][0]][win[i][2][1]] == 0) && (board[win[i][3][0]][win[i][3][1]] == 0))
        || ((board[win[i][0][0]][win[i][0][1]] == 0) && (board[win[i][1][0]][win[i][1][1]] == 0) && (board[win[i][2][0]][win[i][2][1]] == player) && (board[win[i][3][0]][win[i][3][1]] == player)))
            result += 7;
        else if(((board[win[i][0][0]][win[i][0][1]] == player) && (board[win[i][1][0]][win[i][1][1]] == 0) && (board[win[i][2][0]][win[i][2][1]] == player) && (board[win[i][3][0]][win[i][3][1]] == 0))
        || ((board[win[i][0][0]][win[i][0][1]] == 0) && (board[win[i][1][0]][win[i][1][1]] == player) && (board[win[i][2][0]][win[i][2][1]] == 0) && (board[win[i][3][0]][win[i][3][1]] == player)))
            result += 7;
        else if(((board[win[i][0][0]][win[i][0][1]] == player) && (board[win[i][1][0]][win[i][1][1]] == 0) && (board[win[i][2][0]][win[i][2][1]] == 0) && (board[win[i][3][0]][win[i][3][1]] == player)))
            result -= 6;
    return result;
}