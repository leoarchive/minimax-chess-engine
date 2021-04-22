#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "chess.h"
#include "bitboard.h"

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
#define DEPTH 6
int chessboard[64];

void backup(void) {
    for (int i = 0; i < 64; ++i)
        chessboard[i] = board[i];
}

void pass(void) {
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

int get_value(int p) {
    switch (p) {
        case 1:
        case 8: return BLACK_ROOK;
        case 2:
        case 7: return BLACK_KNIGHT;
        case 3:
        case 6: return BLACK_BISHOP;
        case 4: return BLACK_QUEEN;
        case 5: return BLACK_KING;
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 16: return BLACK_PAWN;
        case 17:
        case 18:
        case 19:
        case 20:
        case 21:
        case 22:
        case 23:
        case 24: return PAWN;
        case 25:
        case 32: return ROOK;
        case 26:
        case 31: return KNIGHT;
        case 27:
        case 30: return BISHOP;
        case 28: return QUEEN;
        case 29: return KING;
        default: return 0;
    }
}

int evaluate(void) {
    int white = 0;
    int black = 0;
    for (int i = 0; i < 64; ++i) {
        if (board[i] > 16)
            white += get_value(board[i]);
        else if (board[i])
            black -= get_value(board[i]);
    }
    if (player)
        return white - black;
    else
        return black + white;
}

int piece;
int pos;

void get_move(void) {
    int min_value = 0;
    int max_value = 0;
    bool not = true;
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
                int val = get_value(board[j]);
                if (player) {
                    if (val < min_value) {
                        min_value = val;
                        piece = i;
                        pos = j;
                        not = false;
                    }
                }
                else {
                    if (val > max_value) {
                        max_value = val;
                        piece = i;
                        pos = j;
                        not = false;
                    }
                }
            }
        }
    }
    if (not) {
         do {
             piece = -1;
             pos = 0;
             while (piece < ini) {
                 piece = rand() % end;
             }
             set_bitboard(AN[get_chessboard(piece)]);
             //print_bitboard();
             for (int i = 0; i < 64; ++i) {
                 if (bitboard[i]) {
                     pos = i;
                     break;
                 }
             }
             //printf("piece %s (%d) pos %d ini %d\n", pieces[piece], piece, pos, ini);
         } while (!pos);
    }
}
int p, m;
int search(int d) {
    if (!d)
        return evaluate();
    get_move();
    int cbp = get_chessboard(piece);
    board[pos] = board[cbp];
    board[cbp] = 0;
    if (d == DEPTH) {
        p = piece;
        m = pos;
    }
    SWAP_TURN
    get_move();
    cbp = get_chessboard(piece);
    board[pos] = board[cbp];
    board[cbp] = 0;
    SWAP_TURN
    print_chessboard(0, 8, false);
    system("cls");
    return search(d - 1);
}

void set_move(void) {
    backup();
    int pc, ps;
    int min = INF;
    int max = -INF;
    for (int i = 0; i < 64; ++i) {
        int s = search(DEPTH);
        if (player) {
            if (s > max) {
                max = s;
                pc = p;
                ps = m;
            }
        }
        else {
            if (s < min) {
                min = s;
                pc = p;
                ps = m;
            }
        }
        pass();
    }
    printf("BEST => (%d) piece %s (%s) pos %s search %d atual %d\n", player, pieces[pc], AN[get_chessboard(pc)], AN[ps], min, evaluate());
    set_bitboard(AN[get_chessboard(pc)]);
    print_bitboard();
    int pcc = get_chessboard(pc);
    board[ps] = board[pcc];
    board[pcc] = 0;
    SWAP_TURN
}

void set_move2(void) {
    get_move();
    board[pos] = board[get_chessboard(piece)];
    board[get_chessboard(piece)] = 0;
    SWAP_TURN
}