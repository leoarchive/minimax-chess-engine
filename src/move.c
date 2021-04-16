#include <stdio.h>
#include <stdlib.h>

#include "move.h"

#define WHITE_STRENGTH_PAWN 10
#define WHITE_STRENGTH_KNIGHT 30
#define WHITE_STRENGTH_BISHOP 30
#define WHITE_STRENGTH_ROOK 50
#define WHITE_STRENGTH_QUEEN 90
#define WHITE_STRENGTH_KING 900

#define BLACK_STRENGTH_PAWN (-10)
#define BLACK_STRENGTH_KNIGHT (-30)
#define BLACK_STRENGTH_BISHOP (-30)
#define BLACK_STRENGTH_ROOK (-50)
#define BLACK_STRENGTH_QUEEN (-90)
#define BLACK_STRENGTH_KING (-900)

int best_piece = 0;
int best_position = 0;

int make_move(void) {
    int piece_pos = get_cposition(best_piece);
    int pos_pos = get_cposition(best_position);
    get_bitboard(AN[piece_pos]);
    if (bitboard[piece_pos] && chessboard[piece_pos])
        printf("black %s (%s) killed white %s (%s)\n", pieces[chessboard[piece_pos]], AN[piece_pos], pieces[chessboard[pos_pos]], AN[pos_pos]);

    chessboard[best_position] = chessboard[piece_pos];
    chessboard[piece_pos] = 0;
    player = !player;
    best_piece = 0;
    best_position = 0;
    return 0;
}

int move_generation(void) {
    best_position_and_piece();
    make_move();
    return 0;
}

void best_position_and_piece(void) {
    int all_max_strength = 0;
    for (int piece = 0; piece <= 16; ++piece) {
        int piece_position = get_cposition(piece);
        get_bitboard(AN[piece_position]);

        int position = 0;
        int max_strength = 0;
        for (int i = 0; i < 64; ++i) {
            if (bitboard[i] == 1) {
                int position_strength = get_evaluation(chessboard[i]);
                if (position_strength > max_strength) {
                    max_strength = position_strength;
                    position = i;
                }
            }
        }
        if (max_strength > all_max_strength) {
            all_max_strength = max_strength;
            best_piece = piece;
            best_position = position;
        }
    }

    if (!best_piece)
        aleatory_position();
}

void aleatory_position(void) {
    do {
        best_piece = rand() % 16;
        if (!best_piece)
            continue;
        get_bitboard(AN[get_cposition(best_piece)]);
        for (int i = 0; i < 64; ++i)
            if (bitboard[i] == 1) {
                best_position = i;
                break;
            }
    } while (best_position == 0);
}

int get_cposition(int piece) {
    for (int i = 0; i < 64; ++i)
        if (chessboard[i] == piece)
            return i;
    return 0;
}

int get_evaluation(int piece) {
    switch (piece) {
        case 1:
        case 8:
            return BLACK_STRENGTH_ROOK;
        case 2:
        case 7:
            return BLACK_STRENGTH_KNIGHT;
        case 3:
        case 6:
            return BLACK_STRENGTH_BISHOP;
        case 4:
            return BLACK_STRENGTH_QUEEN;
        case 5:
            return BLACK_STRENGTH_KING;
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 16:
            return BLACK_STRENGTH_PAWN;
        case 17:
        case 18:
        case 19:
        case 20:
        case 21:
        case 22:
        case 23:
        case 24:
            return WHITE_STRENGTH_PAWN;
        case 25:
        case 32:
            return WHITE_STRENGTH_ROOK;
        case 26:
        case 31:
            return WHITE_STRENGTH_KNIGHT;
        case 27:
        case 30:
            return WHITE_STRENGTH_BISHOP;
        case 28:
            return WHITE_STRENGTH_QUEEN;
        case 29:
            return WHITE_STRENGTH_KING;
        default:
            return 0;
    }
}