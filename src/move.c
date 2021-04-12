#include "move.h"

int best_piece = (-1);
int best_position = (-1);

int move_generation(void) {
    best_position_and_piece();

    int piece_position;
    for (piece_position = 0; piece_position < 64; ++piece_position)
        if (chessboard[piece_position] == best_piece)
            break;

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

void best_position_and_piece(void) {
    int max_strength_count = 0;
    for (int piece = 0; piece <= 16; ++piece) {
        int piece_position;
        for (piece_position = 0; piece_position < 64; ++piece_position)
            if (chessboard[piece_position] == piece)
                break;

        create_bitboard((char *) AN[piece_position]);

        int max_strength = 0;
        int position = 0;
        int strength_count = 0;
        for (int i = 0; i < 64; ++i) {
            if (bitboard[i] == 1) {
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
            create_bitboard((char *) AN[piece_position]);
            best_position = rand() % 64;
            if (bitboard[best_position] == 1)
                break;
        } while (1);
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