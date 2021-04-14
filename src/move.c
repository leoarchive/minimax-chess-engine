#include "move.h"

int best_piece = 0;
int best_position = 0;

int acb[64];

bool p = false;

void pass_cb(void) {
    for (int i = 0; i < 64; ++i)
        acb[i] = chessboard[i];
}

void make_move(void) {
    int piece_position = get_cposition(best_piece);
    int validation = move_piece_validation((char *) AN[piece_position], (char *) AN[best_position]);
    if (validation == 2)
        printf("black %s (%s) killed white %s (%s)\n", pieces[best_piece],  AN[piece_position], pieces[chessboard[best_position]], AN[best_position]);
    chessboard[best_position] = chessboard[piece_position];
    chessboard[piece_position] = 0;
    best_piece = 0;
    best_position = 0;
    turn = !turn;
}

void make_move_acb(void) {
    int piece_position = get_cposition(best_piece);
    acb[best_position] = acb[piece_position];
    acb[piece_position] = 0;
}

int cb_evaluation(void) {
    int c = 0;
    for (int i = 0; i < 64; ++i)
        c += get_evaluation(acb[i]);
    return c;
}

int minimax(int d) {
    if (!d)
        return cb_evaluation();
    best_position_and_piece();
    if (p) {
        make_move_acb();
        p = !p;
        int evaluation = minimax(d - 1);
        int max_evaluation = -INFINITY;
        pass_cb();
        if (evaluation > max_evaluation) {
            max_evaluation = evaluation;
            minimax_best_piece = best_piece;
            minimax_best_move = best_position;
            printf("(p) d => %d\nminimax_best_piece %d minimax_best_move %d evaluation %d\n", d, minimax_best_piece, minimax_best_move, evaluation);
        }
    }
    else {
        make_move_acb();
        p = !p;
        int evaluation = minimax(d - 1);
        int min_evaluation = INFINITY;
        pass_cb();
        if (evaluation < min_evaluation) {
            min_evaluation = evaluation;
            minimax_best_piece = best_piece;
            minimax_best_move = best_position;
            printf("(!p) d => %d\nminimax_best_piece %d minimax_best_move %d evaluation %d\n", d, minimax_best_piece, minimax_best_move, evaluation);
        }
    }
    return 0;
}

int move_generation(void) {
    best_position_and_piece();
    make_move();
    return 0;
}

void best_position_and_piece(void) {
    int min, max;
    if (p)
        min = 17, max = 32;
    else
        min = 0, max = 16;

    int all_max_strength = 0;
    int all_min_strength = 0;
    for (int piece = min; piece <= max; ++piece) {
        int piece_position = get_cposition(piece);
        create_bitboard(AN[piece_position]);

        int position = 0;
        int max_strength = 0;
        int min_strength = 0;
        for (int i = 0; i < 64; ++i) {
            if (bitboard[i] == 1) {
                if (p) {
                    int position_strength = get_evaluation(chessboard[i]);
                    if (position_strength < min_strength) {
                        min_strength = position_strength;
                        position = i;
                    }
                }
                else {
                    int position_strength = get_evaluation(chessboard[i]);
                    if (position_strength > max_strength) {
                        max_strength = position_strength;
                        position = i;
                    }
                }
            }
        }

        if (p) {
            if (min_strength < all_min_strength) {
                all_min_strength = min_strength;
                best_piece = piece;
                best_position = position;
                printf("white\nbest_piece %s best_position %s\n", pieces[best_piece], AN[best_position]);
            }
        }
        else {
            if (max_strength > all_max_strength) {
                all_max_strength = max_strength;
                best_piece = piece;
                best_position = position;
                printf("black\nbest_piece %s best_position %s\n", pieces[best_piece], AN[best_position]);
            }
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
        create_bitboard(AN[get_cposition(best_piece)]);
        for (int i = 0; i < 64; ++i)
            if (bitboard[i]) {
                best_position = i;
                break;
            }
    } while (best_position == 0);
    printf("aleatory\nbest_piece %s best_position %s\n", pieces[best_piece], AN[best_position]);
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