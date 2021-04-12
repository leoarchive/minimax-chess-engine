#include <stdio.h>
#include <stdlib.h>

#include "move.h"

int move_generation(void) {
    int piece;
    int best_piece = 0;
    int best_position = 0;

    for (piece = 0; piece <= 16; ++piece) {
        int piece_position = get_best_position(piece);
        if (piece_position > best_position) {
            best_position = piece_position;
            best_piece = piece;
        }
    }

    if (!best_piece)
        best_piece = piece - 1;


    int piece_position;
    for (piece_position = 0; piece_position < 64; ++piece_position)
        if (chessboard[piece_position] == best_piece)
            break;

    if (!best_position) {
        do {
            best_position = rand() % 64;
            if (move_piece_validation((char *) AN[piece_position], (char *) AN[best_position]))
                continue;
        } while (best_position == 0);
    }

    printf("piece %d new position %d\n", best_piece, best_position);
    chessboard[best_position] = chessboard[piece_position];
    chessboard[piece_position] = 0;
    turn = !turn;
    return 0;
}

int get_best_position(int piece) {
    int piece_position;
    for (piece_position = 0; piece_position < 64; ++piece_position)
        if (chessboard[piece_position] == piece)
            break;

    for (size_t j = 0; j < 64; ++j)
        bitboard[j] = move_rules(AN[piece_position], AN[j]);

    int position = 0;
    int max_strength = 0;
    for (int j = 0; j < 64; ++j) {
        if (bitboard[j] == 1) {
            if (move_piece_validation((char *) AN[piece_position], (char *) AN[j]))
                continue;
            if (get_piece_strength((int) chessboard[j]) > max_strength) {
                //printf("max_strength %d\n", max_strength);
                max_strength = get_piece_strength((int) chessboard[j]);
                position = j;
            }
        }
    }

    return position;
}

int get_piece_strength(int piece) {
    switch (piece) {
        case 25:
        case 32:
            return WHITE_STRENGTH_ROOK;
        case 31:
        case 26:
            return WHITE_STRENGTH_KNIGHT;
        case 30:
        case 27:
            return WHITE_STRENGTH_BISHOP;
        case 28:
            return WHITE_STRENGTH_QUEEN;
        case 29:
            return WHITE_STRENGTH_KING;
        case 17:
        case 18:
        case 19:
        case 20:
        case 21:
        case 22:
        case 23:
        case 24:
            return WHITE_STRENGTH_PAWN;
        default:
            return 0;
    }
}