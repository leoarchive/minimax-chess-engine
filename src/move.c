#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "move.h"

int best_piece = (-1);
int best_position = (-1);

int move_generation(void) {
    best_position_and_piece();

    int piece_position;
    for (piece_position = 0; piece_position < 64; ++piece_position)
        if (chessboard[piece_position] == best_piece)
            break;

//    fixed_bitboard((char *) AN[piece_position]);
//    print_fixed_bitboard();

    int validation = move_piece_validation((char *) AN[piece_position], (char *) AN[best_position]);
    if (validation == 2) {
        printf("black %s (%s) killed white %s (%s)\n", pieces[best_piece],  AN[piece_position], pieces[chessboard[best_position]], AN[best_position]);
    }

    chessboard[best_position] = chessboard[piece_position];
    chessboard[piece_position] = 0;
    best_piece = (-1);
    best_position = (-1);
    turn = !turn;
    return 0;
}

void print_fixed_bitboard(void) {
    size_t j = 0;
    for (size_t i = 0; i < 64; ++i, ++j) {
        if (j == 8) {
            j = 0;
            puts("");
        }
        printf("%d ", bitboard_fixed[i]);
    }
    puts("");
}

void best_position_and_piece(void) {
    int max_strength_count = 0;
    for (int piece = 0; piece <= 16; ++piece) {
        int piece_position;
        for (piece_position = 0; piece_position < 64; ++piece_position)
            if (chessboard[piece_position] == piece)
                break;

        fixed_bitboard((char *) AN[piece_position]);

        int max_strength = 0;
        int position = 0;
        int strength_count = 0;
        for (int i = 0; i < 64; ++i) {
            if (bitboard_fixed[i] == 1) {
                int position_strength = get_piece_strength((int) chessboard[i]);
                strength_count += position_strength;
                if (position_strength > max_strength) {
                    max_strength = position_strength;
                    position = i;
                }
            }
        }

        if (strength_count > max_strength_count) {
            max_strength_count = strength_count;
            best_piece = piece;
            best_position = position;
        }
    }

    if (best_piece < 0) {
        do {
            best_piece = rand() % 16;
            if (!best_piece)
                continue;
            int piece_position;
            for (piece_position = 0; piece_position < 64; ++piece_position)
                if (chessboard[piece_position] == best_piece)
                    break;
            fixed_bitboard((char *) AN[piece_position]);
            best_position = rand() % 64;
            if (bitboard_fixed[best_position] == 1)
                break;
        } while (1);
    }
//    printf("best_piece %s best_position %s\n", pieces[best_piece], AN[best_position]);
}

void fixed_bitboard(char *current) {
    for (size_t i = 0; i < 64; ++i) {
        if (move_piece_validation(current, (char *) AN[i]) == 1)
            bitboard_fixed[i] = 0;
        else
            bitboard_fixed[i] = 1;
    }
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