#include <stdio.h>
#include <stdlib.h>

#include "chess.h"
#include "bitboard.h"
#include "move.h"
#include "tables.h"

#define PAWN 10
#define KNIGHT 30
#define BISHOP 30
#define ROOK 50
#define QUEEN 90
#define KING 900
#define BLACK_PAWN (-10)
#define BLACK_KNIGHT (-30)
#define BLACK_BISHOP (-30)
#define BLACK_ROOK (-50)
#define BLACK_QUEEN (-90)
#define BLACK_KING (-900)

#define INF 99999
#define DEPTH 8

int chessboard[64];

int get_value(int p, int s);
void get_move(void);
int evaluate(void);
int search(int d);

int piece_aux, move_aux;

void save_board(void) {
    for (int i = 0; i < 64; ++i)
        chessboard[i] = board[i];
}

void unmove(void) {
    for (int i = 0; i < 64; ++i)
        board[i] = chessboard[i];
}

int get_chessboard(int p) {
    for (int i = 0; i < 64; ++i) {
        if (board[i] == p)
            return i;
    }
    return 0;
}

int evaluate(void) {
    int white = 0;
    int black = 0;
    for (int i = 0; i < 64; ++i) {
        if (board[i] > 16)
            white += get_value(i, i);
        else if (board[i])
            black -= get_value(i, i);
    }
    if (player)
        return white - black;
    else
        return black + white;
}

void move_generation(void) {
    save_board();
    int piece, move;
    int min = INF;
    int max = -INF;
    int s;
    for (int i = 0; i < 16; ++i) {
        s = search(DEPTH);
        if (player) {
            if (s > max) {
                max = s;
                piece = piece_aux;
                move = move_aux;
            }
        }
        else {
            if (s < min) {
                min = s;
                piece = piece_aux;
                move = move_aux;
            }
        }
        unmove();
    }
    int piece_value = get_chessboard(piece);
    board[move] = board[piece_value];
    board[piece_value] = 0;
    SWAP_TURN
}

int piece;
int pos;

int search(int d) {
    if (!d)
        return evaluate();
    get_move();
    int piece_val = get_chessboard(piece);
    board[pos] = board[piece_val];
    board[piece_val] = 0;
    if (d == DEPTH) {
        piece_aux = piece;
        move_aux = pos;
    }
    print_chessboard(0, 8, false);
    system(CLEAR);
    SWAP_TURN
    get_move();
    piece_val = get_chessboard(piece);
    board[pos] = board[piece_val];
    board[piece_val] = 0;
    print_chessboard(0, 8, false);
    system(CLEAR);
    SWAP_TURN
    return search(d - 1);
}

void get_move(void) {
    int min_value = 0;
    int max_value = 0;
    bool getend = true;
    int ini;
    int end;
    if (player)
        ini = 17, end = 32;
    else
        ini = 0, end = 16;
    for (int i = ini; i <= end; ++i) {
        set_bitboard(AN[get_chessboard(i)]);
        for (int j = 0; j < 64; ++j) {
            if (bitboard[j]) {
                int val = get_value(j, j);
                if (player) {
                    if (val < min_value) {
                        min_value = val;
                        piece = i;
                        pos = j;
                        getend = false;
                    }
                }
                else {
                    if (val > max_value) {
                        max_value = val;
                        piece = i;
                        pos = j;
                        getend = false;
                    }
                }
            }
        }
    }
    if (getend) {
         do {
             piece = -1;
             int pb_max = 0;
             while (piece < ini)
                 piece = rand() % end;
             set_bitboard(AN[get_chessboard(piece)]);
             for (int i = 0; i < 64; ++i) {
                 if (bitboard[i]) {
                     int pb = get_value(get_chessboard(piece), i);
                     if (player) {
                         if (pb > pb_max) {
                             pb_max = pb;
                             pos = i;
                         }
                     }
                     else {
                         if (pb < pb_max) {
                             pb_max = pb;
                             pos = i;
                         }
                     }
                     getend = false;
                 }
             }
         } while (getend);
    }
}

int get_value(int p, int s) {
    switch (board[p]) {
        case 1:
        case 8: return BLACK_ROOK - black_rook[s];
        case 2:
        case 7: return BLACK_KNIGHT - black_knight[s];
        case 3:
        case 6: return BLACK_BISHOP - black_bishop[s];
        case 4: return BLACK_QUEEN - black_queen[s];
        case 5: return BLACK_KING - black_king[s];
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 16: return BLACK_PAWN - black_pawn[s];
        case 17:
        case 18:
        case 19:
        case 20:
        case 21:
        case 22:
        case 23:
        case 24: return PAWN + white_pawn[s];
        case 25:
        case 32: return ROOK + white_rook[s];
        case 26:
        case 31: return KNIGHT + white_knight[s];
        case 27:
        case 30: return BISHOP + white_bishop[s];
        case 28: return QUEEN + white_queen[s];
        case 29: return KING + white_king[s];
        default: return 0;
    }
}