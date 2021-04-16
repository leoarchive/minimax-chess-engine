#include <stdio.h>
#include <stdlib.h>

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

int make(void) {
    int piece_pos = get_chessboard(piece);
    int pos_pos = get_chessboard(position);

    set_bitboard(AN[piece_pos]);
    if (bitboard[piece_pos] && board[piece_pos])
        printf("black %s (%s) killed white %s (%s)\n", pieces[board[piece_pos]], AN[piece_pos], pieces[board[pos_pos]], AN[pos_pos]);

    board[position] = board[piece_pos];
    board[piece_pos] = 0;
    piece = 0;
    position = 0;
    SWAP_TURN
    return 0;
}

int generation(void) {
    set_move();
    make();
    return 0;
}

void set_move(void) {
    int all_max_val = 0;
    for (int i = 0; i <= 16; ++i) {
        int p_pos = get_chessboard(i);
        set_bitboard(AN[p_pos]);

        int p = 0;
        int max_val = 0;
        for (int j = 0; j < 64; ++j) {
            if (bitboard[j] == 1) {
                int pos_val = get_evaluation(board[j]);
                if (pos_val > max_val) {
                    max_val = pos_val;
                    p = j;
                }
            }
        }
        if (max_val > all_max_val) {
            all_max_val = max_val;
            piece = i;
            position = p;
        }
    }

    if (!piece)
        set_aleatory();
}

void set_aleatory(void) {
    do {
        piece = rand() % 16;
        if (!piece)
            continue;
        set_bitboard(AN[get_chessboard(piece)]);
        for (int i = 0; i < 64; ++i)
            if (bitboard[i] == 1) {
                position = i;
                break;
            }
    } while (!position);
}

int get_chessboard(int p) {
    for (int i = 0; i < 64; ++i)
        if (board[i] == p)
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