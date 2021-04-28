#include <stdlib.h>
#include <stdio.h>

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
#define DEPTH 3
#define TIMES 32

typedef struct moves{
    int from;
    int to;
}MOVE;

int aux_board[64];
int LIST[TIMES * 2];
int EVAL[TIMES];
int from_aux, to_aux;
int cnt = 0;

MOVE get_move(void);
int get_value(int p, int s);
int evaluate(void);

void save_board(void) {
    for (int i = 0; i < 64; ++i)
        aux_board[i] = board[i];
}

void unmove(void) {
    for (int i = 0; i < 64; ++i)
        board[i] = aux_board[i];
}

void make_move(int f, int t) {
    board[t] = board[f];
    board[f] = 0;
    SWAP_TURN
}

int get_chessboard(int p) {
    for (int i = 0; i < 64; ++i)
        if (board[i] == p)
            return i;
    return 0;
}

int evaluate(void) {
    int wht = 0;
    int blk = 0;
    for (int i = 0; i < 64; ++i) {
        if (board[i] > 16)
            wht += get_value(i, i);
        else if (board[i])
            blk -= get_value(i, i);
    }
    if (player)
        return wht - blk;
    else
        return blk + wht;
}

int minimax(int d);
void LIST_init(void);

void move_generation(void) {
    save_board();
    LIST_init();
    for (int i = 0; i < TIMES; ++i)
        EVAL[i] = 0;
    int from, to;
    int min = INF;
    int max = -INF;
    int eval;
    for (int i = 0; i < TIMES; ++i) {
        eval = minimax(DEPTH);
        EVAL[i] = eval;
        if (player) {
            if (eval > max) {
                max = eval;
                from = from_aux;
                to = to_aux;
            }
        }
        else {
            if (eval < min) {
                min = eval;
                from = from_aux;
                to = to_aux;
            }
        }
        unmove();
    }
    int piece_value = get_chessboard(from);
    set_bitboard(AN[piece_value]);
    printf("black: %s %s\n", AN[piece_value], AN[to]);
    if (board[to]) {
        if (player)
            w_cap[w_cnt++] = board[to];
        else
            b_cap[b_cnt++] = board[to];
    }
    print_capture();
    make_move(piece_value, to);
}

void LIST_init(void) {
    cnt = 0;
    for (int i = 0; i < (TIMES * 2); ++i)
        LIST[i] = 0;
}

int LIST_verify(int f, int t) {
    for (int i = 0; i < (TIMES * 2); i+=2)
        if (LIST[i] == f && LIST[i+1] == t)
            return 1;
    return 0;
}

void LIST_print(void) {
    int j = 0;
    for (int i = 0; i < (TIMES * 2); i+=2, j++)
        printf("[%d] from %s(%d) to %s eval %d\n", i, pieces[LIST[i]], LIST[i], AN[LIST[i+1]], EVAL[j]);
}

MOVE aleatory(int min_piece, int max_piece);

int minimax(int d) {
    if (!d)
        return evaluate();
    MOVE get;
    get = get_move();
    if (d == DEPTH) {
        if (LIST_verify(get.from, get.to))
            get = aleatory(BLACKINIT, BLACKEND);
        from_aux = get.from,
        to_aux = get.to,
        LIST[cnt] = from_aux,
        LIST[cnt + 1] = to_aux,
        cnt += 2;
    }
    make_move(get_chessboard(get.from), get.to);
    //print_chessboard(0, 8, false);
    //system(CLEAR);
    get = get_move();
    make_move(get_chessboard(get.from), get.to);
    //print_chessboard(0, 8, false);
    //system(CLEAR);
    return minimax(d - 1);
}

MOVE get_move(void) {
    MOVE get;
    int min = 0;
    int max = 0;
    int eval;
    int min_piece;
    int max_piece;
    bool end = false;
    if (player)
        min_piece = WHITEINIT,
        max_piece = WHITEEND;
    else
        min_piece = BLACKINIT,
        max_piece = BLACKEND;
    for (int i = min_piece; i <= max_piece; ++i) {
        set_bitboard(AN[get_chessboard(i)]);
        for (int j = 0; j < 64; ++j) {
            if (bitboard[j]) {
                eval = get_value(j, j);
                if (player) {
                    if (eval < min)
                        get.from = i,
                        get.to = j,
                        min = eval,
                        end = true;
                }
                else {
                    if (eval > max)
                        get.from = i,
                        get.to = j,
                        max = eval,
                        end = true;
                }
            }
        }
    }
    if (!end)
        return aleatory(min_piece, max_piece);
    return get;
}

MOVE aleatory(int min_piece, int max_piece) {
    MOVE get;
    bool end = false;
    int eval;
    do {
        int min = INF;
        int max = -INF;
        get.from = 0;
        while (get.from < min_piece)
            get.from = rand() % max_piece;
        set_bitboard(AN[get_chessboard(get.from)]);
        for (int i = 0; i < 64; ++i) {
            if (bitboard[i]) {
                eval = get_value(get_chessboard(get.from), i);
                if (player) {
                    if (eval > max)
                        get.to = i,
                        max = eval;
                }
                else {
                    if (eval < min)
                        get.to = i,
                        min = eval;
                }
                end = true;
            }
        }
    } while (!end);
    return get;
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