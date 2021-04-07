/*
    Dumb, a chess engine
    Copyright (C) 2021 Leonardo Zamboni

    Dumb is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Dumb is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
#include <stdio.h>

#include "chess.h"
#include "search.h"

int bpp = 0;

const char *search(void) {
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
                            for (size_t l = 0; l < 64; ++l)
                                bitboard[l] = move_rules(AN[j], AN[l]);
                            if (bishop_validation(AN[j], AN[k]) || rook_validation(AN[j], AN[k]))
                                continue;
                            for (size_t l = 0; l < 64; ++l)
                                bitboard[l] = move_rules(AN[i], AN[l]);
                            if (bishop_validation(AN[i], AN[k]) || rook_validation(AN[i], AN[k]))
                                continue;
                            printf("piece %s goto %s killed by %s\n", AN[j], AN[k], AN[i]);
                            return AN[k];
                        }
                    }
                }
            }
            bpp++;
            return search();
        }
        else {
            bpp++;
            return search();
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
                            for (size_t l = 0; l < 64; ++l)
                                bitboard[l] = move_rules(AN[j], AN[l]);
                            if (bishop_validation(AN[j], AN[k]) || rook_validation(AN[j], AN[k]))
                                continue;
                            for (size_t l = 0; l < 64; ++l)
                                bitboard[l] = move_rules(AN[i], AN[l]);
                            if (bishop_validation(AN[i], AN[k]) || rook_validation(AN[i], AN[k]))
                                continue;
                            printf("piece %s goto %s killed by %s\n", AN[j], AN[k], AN[i]);
                            return AN[k];
                        }
                    }
                }
            }
            bpp++;
            return search();
        }
        else {
            bpp++;
            return search();
        }
    }
}
