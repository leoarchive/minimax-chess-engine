#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "move.h"
#include "chess.h"
#include "bitboard.h"

#define WHITE_PAWN_VAL 10
#define WHITE_KNIGHT_VAL 30
#define WHITE_BISHOP_VAL 30
#define WHITE_ROOK_VAL 50
#define WHITE_QUEEN_VAL 90
#define WHITE_KING_VAL 900

#define BLACK_PAWN_VAL (-10)
#define BLACK_KNIGHT_VAL (-30)
#define BLACK_BISHOP_VAL (-30)
#define BLACK_ROOK_VAL (-50)
#define BLACK_QUEEN_VAL (-90)
#define BLACK_KING_VAL (-900)

int piece = 0;
int position = 0;

int chessboard[64];
void set_bitboard_move(char *f);
int make(void) {
    int piece_pos = get_chessboard(piece);
    int pos_pos = get_chessboard(position);

    set_bitboard_move(AN[piece_pos]);
    if (bitboard[piece_pos] && board[piece_pos])
        printf("black %s (%s) killed white %s (%s)\n", pieces[board[piece_pos]], AN[piece_pos], pieces[board[pos_pos]], AN[pos_pos]);

    chessboard[position] = chessboard[piece_pos];
    chessboard[piece_pos] = 0;
    piece = 0;
    position = 0;
    SWAP_TURN
    return 0;
}
int piece_move;
int position_move;

int make_finaly(void) {
    int piece_pos = get_chessboard(piece_move);
    board[position_move] = board[piece_pos];
    board[piece_pos] = 0;
    piece_move = 0;
    position_move = 0;
    SWAP_TURN
    SWAP_TURN
    return 0;
}
int get_rules_move(char *f, char *t);
void set_bitboard_move(char *f) {
    for (size_t i = 0; i < 64; ++i) {
        if (get_rules_move(f, AN[i]) == 1)
            bitboard[i] = 1;
        else
            bitboard[i] = 0;
    }
}

int get_rules_move(char *f, char *t) {
    if (!strcmp(f, t)) return 0;
    from_value  =   f[1] - '0';
    to_value    =   t[1] - '0';
    from_char   =   f[0];
    to_char     =   t[0];
    from_pos    =   chessboard[get_position(f)];
    to_pos      =   chessboard[get_position(t)];
    if (!from_pos)  return 0;

    if (player) {   if (from_pos < 17)          return 0;}
    else        {   if (from_pos > 16)          return 0;}

    if (from_pos > 16 && from_pos < 25 || from_pos > 8 && from_pos < 17)            return pawn();
    else if (from_pos == 27 || from_pos == 30 || from_pos == 3 || from_pos == 6)    return bishop(f, t);
    else if (from_pos == 26 || from_pos == 31 || from_pos == 2 || from_pos == 7)    return knight();
    else if (from_pos == 25 || from_pos == 32 || from_pos == 1 || from_pos == 8)    return rook(f, t);
    else if (from_pos == 28 || from_pos == 4)   return queen(f, t);
    else if (from_pos == 29 || from_pos == 5)   return king();
    return 1;
}
void min(void);
void pass(void);
int generation(void) {
    pass();
    min();
    make_finaly();
    return 0;
}

void pass(void) {
    for (int i = 0; i < 64; ++i)
        chessboard[i] = board[i];
}

int evaluation(void) {
    int eval = 0;
    for (int i = 0; i < 64; ++i)
       eval += get_evaluation(chessboard[i]);
    return eval;
}

int max(void) {
    for (int i = 17; i <= 32; ++i) {
        int p_pos = get_chessboard(i);
        set_bitboard_move(AN[p_pos]);
        for (int j = 0; j < 64; ++j) {
            if (bitboard[j]) {
                piece = i;
                position = j;
                make();
                int max_val = evaluation();
                return max_val;
            }
        }
    }
    return 0;
}

void min(void) {
    int all_min_val = 9999999;
    for (int i = 0; i <= 16; ++i) {
        int p_pos = get_chessboard(i);
        set_bitboard_move(AN[p_pos]);
        int max_val;
        int min_val;
        int j;
        for (j = 0; j < 64; ++j) {
            if (bitboard[j]) {
                piece = i;
                position = j;
                make();
                min_val = evaluation();
                max_val = max();
            }
        }
        if (max_val > 0)
            max_val *= (-1);
        if (min_val < all_min_val && min_val < max_val) {
            all_min_val = min_val;
            piece_move = i;
            position_move = j;
        }
        pass();
    }
    if (!piece_move)
        set_aleatory();
}

void set_aleatory(void) {
    do {
        piece_move = rand() % 16;
        if (!piece)
            continue;
        set_bitboard(AN[get_chessboard(piece_move)]);
        for (int i = 0; i < 64; ++i)
            if (bitboard[i]) {
                position_move = i;
                break;
            }
    } while (!position_move);
}

int get_chessboard(int p) {
    for (int i = 0; i < 64; ++i)
        if (chessboard[i] == p)
            return i;
    return 0;
}

int get_evaluation(int p) {
    switch (p) {
        case 1:
        case 8:
            return BLACK_ROOK_VAL;
        case 2:
        case 7:
            return BLACK_KNIGHT_VAL;
        case 3:
        case 6:
            return BLACK_BISHOP_VAL;
        case 4:
            return BLACK_QUEEN_VAL;
        case 5:
            return BLACK_KING_VAL;
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 16:
            return BLACK_PAWN_VAL;
        case 17:
        case 18:
        case 19:
        case 20:
        case 21:
        case 22:
        case 23:
        case 24:
            return WHITE_PAWN_VAL;
        case 25:
        case 32:
            return WHITE_ROOK_VAL;
        case 26:
        case 31:
            return WHITE_KNIGHT_VAL;
        case 27:
        case 30:
            return WHITE_BISHOP_VAL;
        case 28:
            return WHITE_QUEEN_VAL;
        case 29:
            return WHITE_KING_VAL;
        default:
            return 0;
    }
}