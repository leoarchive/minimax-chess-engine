#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "chess.h"
#include "search.h"

int bpp = 0;

const char *search(Stack *s) {
    if (bpp > 15)
        return NULL;
    unsigned int abb[64];
    int bp[] = {white_king,white_queen,white_rook,white_rook2,white_knight,white_knight2,white_bishop,white_bishop2,
                white_pawn1,white_pawn2,white_pawn3,white_pawn4,white_pawn5,white_pawn6,white_pawn7,white_pawn8};
    int bpb[] = {black_king,black_queen,black_rook,black_rook2,black_knight,black_knight2,black_bishop,black_bishop2,
                 black_pawn1,black_pawn2,black_pawn3,black_pawn4,black_pawn5,black_pawn6,black_pawn7,black_pawn8};
    bool no = true;
    int j;
    if (turn) {
        for (j = 0; j < 64; ++j) {
            if (chessboard[j] == bp[bpp])
                break;
        }
        for (int i = 0; i < 64; ++i) {
            bb[i] = move_rules(AN[j], AN[i]);
            if (bb[i] == 1)
                no = false;
        }
        if (!no) {
            for (int i = 0; i < 64; ++i) {
                if (chessboard[i] < 17 && chessboard[i] > 0) {
                    for (int k = 0; k < 64; ++k) {
                        abb[k] = move_rules(AN[i], AN[k]);
                        if (abb[k] == 1 && bb[k] == 1) {
//                            for (size_t l = 0; l < 64; ++l)
//                                bitboard[l] = move_rules(AN[j], AN[l]);
//                            if (bishop_validation(AN[j], AN[k]) || rook_validation(AN[j], AN[k]))
//                                continue;
//                            for (size_t l = 0; l < 64; ++l)
//                                bitboard[l] = move_rules(AN[i], AN[l]);
//                            if (bishop_validation(AN[i], AN[k]) || rook_validation(AN[i], AN[k]))
//                                continue;
                            int val = move_piece_verify(AN[j], AN[k]);
                            if (val)
                                continue;
                            else {
                                move_piece(AN[j], AN[k]);
                            }
                            int valK = move_piece_verify(AN[i], AN[k]);
                            if (valK)
                                continue;
                            else
                                move_piece(AN[i], AN[k]);
                            printf("piece %s goto %s killed by %s\n", AN[j], AN[k], AN[i]);
                            return AN[k];
                        }
                    }
                }
            }
            bpp++;
            return search(s);
        }
        else {
            bpp++;
            return search(s);
        }
    }
    else {
        for (j = 0; j < 64; ++j) {
            if (chessboard[j] == bpb[bpp])
                break;
        }
        for (int i = 0; i < 64; ++i) {
            bb[i] = move_rules(AN[j], AN[i]);
            if (bb[i] == 1)
                no = false;
        }
        if (!no) {
            for (int i = 0; i < 64; ++i) {
                if (chessboard[i] > 16) {
                    for (int k = 0; k < 64; ++k) {
                        abb[k] = move_rules(AN[i], AN[k]);
                        if (abb[k] == 1 && bb[k] == 1) {
//                            for (size_t l = 0; l < 64; ++l)
//                                bitboard[l] = move_rules(AN[j], AN[l]);
//                            if (bishop_validation(AN[j], AN[k]) || rook_validation(AN[j], AN[k]))
//                                continue;
//                            for (size_t l = 0; l < 64; ++l)
//                                bitboard[l] = move_rules(AN[i], AN[l]);
//                            if (bishop_validation(AN[i], AN[k]) || rook_validation(AN[i], AN[k]))
//                                continue;
                            int val = move_piece_verify(AN[j], AN[k]);
                            if (val)
                                continue;
                            else {
                                move_piece(AN[j], AN[k]);
                            }
                            int valK = move_piece_verify(AN[i], AN[k]);
                            if (valK) {
                                continue;
                            }
                            else
                                move_piece(AN[i], AN[k]);
                            printf("piece %s goto %s killed by %s\n", AN[j], AN[k], AN[i]);
                            return AN[k];
                        }
                    }
                }
            }
            bpp++;
            return search(s);
        }
        else {
            bpp++;
            return search(s);
        }
    }
}

int move_piece_verify(const char *current, const char *new) {
    int current_position;
    for (current_position = 0; current_position < 64; ++current_position)
        if (strcmp(AN[current_position], current) == 0)
            break;

    if (!chessboard[current_position])
        return 1;

    int new_position;
    for (new_position = 0; new_position < 64; ++new_position)
        if (strcmp(AN[new_position], new) == 0)
            break;

    for (size_t j = 0; j < 64; ++j)
        bitboard[j] = move_rules(current, AN[j]);

    int validation = bishop_validation(current, new);

    if (validation == 1)
        return 1;

    if (validation != new_position && validation != 0)
        return 1;

    validation = rook_validation(current, new);

    if (validation == 1)
        return 1;

    if (validation != new_position && validation != 0)
        return 1;

    if (!bitboard[new_position])
        return 1;

    if (chessboard[new_position] != 0)
        printf("%s (%s) killed %s (%s)\n", pieces[chessboard[current_position]], AN[current_position], pieces[chessboard[new_position]], AN[new_position]);
    return 0;
}