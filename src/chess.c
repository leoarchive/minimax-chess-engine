#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "chess.h"

#ifdef LINUX
const char *pieces[] = {
        " ",
        "♜","♞","♝","♛","♚","♝","♞","♜",
        "♟","♟","♟","♟","♟","♟","♟","♟",
        "♙","♙","♙","♙","♙","♙","♙","♙",
        "♖","♘","♗","♕","♔","♗","♘","♖"
};
#else
const char *pieces[] = {
        " ",
        "R","N","B","Q","K","B","N","R",
        "P","P","P","P","P","P","P","P",
        "P","P","P","P","P","P","P","P",
        "R","N","B","Q","K","B","N","R"
};
#endif

const char *AN[] = {
        "a8","b8","c8","d8","e8","f8","g8","h8",
        "a7","b7","c7","d7","e7","f7","g7","h7",
        "a6","b6","c6","d6","e6","f6","g6","h6",
        "a5","b5","c5","d5","e5","f5","g5","h5",
        "a4","b4","c4","d4","e4","f4","g4","h4",
        "a3","b3","c3","d3","e3","f3","g3","h3",
        "a2","b2","c2","d2","e2","f2","g2","h2",
        "a1","b1","c1","d1","e1","f1","g1","h1"
};

unsigned int chessboard[] = {
        black_rook,black_knight,black_bishop,black_queen,black_king,black_bishop2,black_knight2,black_rook2,
        black_pawn1,black_pawn2,black_pawn3,black_pawn4,black_pawn5,black_pawn6,black_pawn7,black_pawn8,
        empty,empty,empty,empty,empty,empty,empty,empty,
        empty,empty,empty,empty,empty,empty,empty,empty,
        empty,empty,empty,empty,empty,empty,empty,empty,
        empty,empty,empty,empty,empty,empty,empty,empty,
        white_pawn1,white_pawn2,white_pawn3,white_pawn4,white_pawn5,white_pawn6,white_pawn7,white_pawn8,
        white_rook,white_knight,white_bishop,white_queen,white_king,white_bishop2,white_knight2,white_rook2,
};

bool turn = true;

void print_chessboard(void) {
    int j = 0, c = 0, n = 8;
    for (size_t i = 0; i < 64; ++i, ++j) {
        if (j == 8) {
            j = 0;
            puts("");
        }
        else
            c = !c;
        if (!j)
            printf("%d ", n--);
        printf("%s", c == 1 ? WHT : BLK);
        printf("%s ", pieces[chessboard[i]]);
        printf("\033[0m");
    }

    printf("\n  ");

    char l = 'a';
    while (l != 'i')
        printf("%c ", l++);
    puts("");
}

void print_bitboard(void) {
    size_t j = 0;
    for (size_t i = 0; i < 64; ++i, ++j) {
        if (j == 8) {
            j = 0;
            puts("");
        }
        printf("%d ", bitboard[i]);
    }
    puts("");
}

int move_piece_validation(char *current, char *new) {
    int current_position = get_chessboard_position(current);

    if (!chessboard[current_position])
        return 1;

    int new_position = get_chessboard_position(new);

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

    if (turn) {
        if (chessboard[current_position] < 17)
            return 1;
    }
    else {
        if (chessboard[current_position] > 16)
            return 1;
    }

    if (chessboard[new_position] != 0)
        printf("%s (%s) killed %s (%s)\n", pieces[chessboard[current_position]], AN[current_position], pieces[chessboard[new_position]], AN[new_position]);

    return 0;
}

int move_piece(void) {
    char *current = (char *) malloc(2 * sizeof(char));
    char *new = (char *) malloc(2 * sizeof(char));
    printf("%s: ", turn ? "white" : "black");
    scanf(" %s %s", current, new);

    if (move_piece_validation(current, new)) {
        printf("invalid move");
        return 1;
    }

    int current_position = get_chessboard_position(current);
    int new_position = get_chessboard_position(new);

    chessboard[new_position] = chessboard[current_position];
    chessboard[current_position] = 0;
    turn = !turn;
    return 0;
}

void back_stack(Stack *s) {
    pull_stack(s);
    Node *w = s->top;
    for (size_t i = 0; i < 64; ++i)
        chessboard[i] = w->cb[i];
    turn = !turn;
}

int move_rules(const char *current_algebraic_notation, const char *new_algebraic_notation) {
    if (!generic_rule_verify(current_algebraic_notation, new_algebraic_notation))
        return 0;

    int current_chessboard_position = get_chessboard_position(current_algebraic_notation);

    if (chessboard[current_chessboard_position] > 16 && chessboard[current_chessboard_position] < 25)
        return white_pawn_rule(current_algebraic_notation, new_algebraic_notation);

    if (chessboard[current_chessboard_position] == 27 || chessboard[current_chessboard_position] == 30)
        return white_bishop_rule(current_algebraic_notation, new_algebraic_notation);

    if (chessboard[current_chessboard_position] == 26 || chessboard[current_chessboard_position] == 31)
        return white_knight_rule(current_algebraic_notation, new_algebraic_notation);

    if (chessboard[current_chessboard_position] == 25 || chessboard[current_chessboard_position] == 32)
        return white_rook_rule(current_algebraic_notation, new_algebraic_notation);

    if (chessboard[current_chessboard_position] == 28) {
        if (!white_rook_rule(current_algebraic_notation, new_algebraic_notation) &&
            !white_bishop_rule(current_algebraic_notation, new_algebraic_notation))
            return 0;
    }

    if (chessboard[current_chessboard_position] == 29)
        return white_king_rule(current_algebraic_notation, new_algebraic_notation);

    /* ----------------------------------------------------------------------------------------------- */

    if (chessboard[current_chessboard_position] > 8 && chessboard[current_chessboard_position] < 17)
        return black_pawn_rule(current_algebraic_notation, new_algebraic_notation);

    if (chessboard[current_chessboard_position] == 3 || chessboard[current_chessboard_position] == 6)
        return black_bishop_rule(current_algebraic_notation, new_algebraic_notation);

    if (chessboard[current_chessboard_position] == 2 || chessboard[current_chessboard_position] == 7)
        return black_knight_rule(current_algebraic_notation, new_algebraic_notation);

    if (chessboard[current_chessboard_position] == 1 || chessboard[current_chessboard_position] == 8)
        return black_rook_rule(current_algebraic_notation, new_algebraic_notation);

    if (chessboard[current_chessboard_position] == 4) {
        if (!black_rook_rule(current_algebraic_notation, new_algebraic_notation) &&
            !black_bishop_rule(current_algebraic_notation, new_algebraic_notation))
            return 0;
    }

    if (chessboard[current_chessboard_position] == 5)
        return black_king_rule(current_algebraic_notation, new_algebraic_notation);

    return 1;
}

int get_chessboard_position(const char *piece_algebraic_notation) {
    for (int pos = 0; pos < 64; ++pos)
        if (strcmp(AN[pos], piece_algebraic_notation) == 0)
            return pos;
    return 0;
}

int generic_rule_verify(const char *current_algebraic_notation, const char *new_algebraic_notation) {
    if (strcmp(current_algebraic_notation, new_algebraic_notation) == 0)
        return 0;
    return 1;
}

int verify_validation(char *diagonal_algebraic_notation[], int current, int new) {
    int k;
    if (current > new) {
        for (int j = current - 1; j >= new; --j) {
            for (k = 0; k < 64; ++k)
                if (strcmp(AN[k], diagonal_algebraic_notation[j]) == 0)
                    break;
            if (turn) {
                if (chessboard[k] > 16) {
                    return 1;
                }
                else if (chessboard[k] < 17 && chessboard[k] > 0) {
                    return k;
                }
            }
            if (!turn) {
                if (chessboard[k] < 17 && chessboard[k] > 0) {
                    return 1;
                }
                else if (chessboard[k] > 16) {
                    return k;
                }
            }
        }
    }
    else {
        for (int j = current + 1; j <= new; ++j) {
            for (k = 0; k < 64; ++k)
                if (strcmp(AN[k], diagonal_algebraic_notation[j]) == 0)
                    break;
            if (!turn) {
                if (chessboard[k] > 16) {
                    return 1;
                }
                else if (chessboard[k] < 17 && chessboard[k] > 0) {
                    return k;
                }
            }
            if (turn) {
                if (chessboard[k] < 17 && chessboard[k] > 0) {
                    return 1;
                }
                else if (chessboard[k] > 16) {
                    return k;
                }
            }
        }
    }
    return 0;
}

int bishop_validation(const char *current_algebraic_notation, const char *new_algebraic_notation) {
    int current_chessboard_position = get_chessboard_position(current_algebraic_notation);
    if (chessboard[current_chessboard_position] != 27 && chessboard[current_chessboard_position] != 30
    && chessboard[current_chessboard_position] != 3 && chessboard[current_chessboard_position] != 6
    && chessboard[current_chessboard_position] != 4 && chessboard[current_chessboard_position] != 28)
        return 0;

    char *diagonal_algebraic_notation[] = {
            "a8","b8","a7","c8","b7","a6","d8","c7", "b6","a5","e8","d7","c6","b5","a4","f8",
            "e7","d6","c5","b4","a3","g8","f7","e6", "d5","c4","b3","a2","h8","g7","f6","e5",
            "d4","c3","b2","a1","h7","g6","f5","e4", "d3","c2","b1","h6","g5","f4","e3","d2",
            "c1","h5","g4","f3","e2","d1","h4","g3", "f2","e1","h3","g2","f1","h2","g1","h1",
            "h8","g8","h7","f8","g7","h6","e8","f7", "g6","h5","d8","e7","f6","g5","h4","c8",
            "d7","e6","f5","g4","h3","b8","c7","d6", "e5","f4","g3","h2","a8","b7","c6","d5",
            "e4","f3","g2","h1","a7","b6","c5","d4", "e3","f2","g1","a6","b5","c4","d3","e2",
            "f1","a5","b4","c3","d2","e1","a4","b3", "c2","d1","a3","b2","c1","a2","b1","a1"
    };

    for (int i = 0; i < 128; ++i) {
        if (strcmp(diagonal_algebraic_notation[i], current_algebraic_notation) == 0) {
            for (int j = 0; j < 128; ++j) {
                if (strcmp(diagonal_algebraic_notation[j], new_algebraic_notation) == 0) {
                    if ((j - i) < -8 || (j - i) > 8)
                        continue;
                    else
                        return verify_validation(diagonal_algebraic_notation, i, j);
                }
            }
        }
    }
    return 0;
}

int rook_validation(const char *current_algebraic_notation, const char *new_algebraic_notation) {
    int current_chessboard_position = get_chessboard_position(current_algebraic_notation);
    if (chessboard[current_chessboard_position] != 25 && chessboard[current_chessboard_position] != 32
        && chessboard[current_chessboard_position] != 1 && chessboard[current_chessboard_position] != 8
        && chessboard[current_chessboard_position] != 4 && chessboard[current_chessboard_position] != 28)
        return 0;

    char *vertical_and_horizontal_a_n[] = {
            "a8","b8","c8","d8","e8","f8","g8","h8", "a7","b7","c7","d7","e7","f7","g7","h7",
            "a6","b6","c6","d6","e6","f6","g6","h6", "a5","b5","c5","d5","e5","f5","g5","h5",
            "a4","b4","c4","d4","e4","f4","g4","h4", "a3","b3","c3","d3","e3","f3","g3","h3",
            "a2","b2","c2","d2","e2","f2","g2","h2", "a1","b1","c1","d1","e1","f1","g1","h1",
            "a8","a7","a6","a5","a4","a3","a2","a1", "b8","b7","b6","b5","b4","b3","b2","b1",
            "c8","c7","c6","c5","c4","c3","c2","c1", "d8","d7","d6","d5","d4","d3","d2","d1",
            "e8","e7","e6","e5","e4","e3","e2","e1", "f8","f7","f6","f5","f4","f3","f2","f1",
            "g8","g7","g6","g5","g4","g3","g2","g1", "h8","h7","h6","h5","h4","h3","h2","h1",
    };

    for (int i = 0; i < 128; ++i) {
        if (strcmp(vertical_and_horizontal_a_n[i], current_algebraic_notation) == 0) {
            for (int j = 0; j < 128; ++j) {
                if (strcmp(vertical_and_horizontal_a_n[j], new_algebraic_notation) == 0) {
                    if ((j - i) < -8 || (j - i) > 8)
                        continue;
                    else
                        return verify_validation(vertical_and_horizontal_a_n, i, j);
                }
            }
        }
    }
    return 0;
}

int white_pawn_rule(const char *current_algebraic_notation, const char *new_algebraic_notation) {
    bool walk_two_houses = false;
    if (current_algebraic_notation[1] == '2')
        walk_two_houses = true;

    int current_position_value = current_algebraic_notation[1] - '0';
    int new_position_value = new_algebraic_notation[1] - '0';

    int chessboard_position_value = get_chessboard_position(new_algebraic_notation);

    if (chessboard[chessboard_position_value] < 17 && chessboard[chessboard_position_value] > 0
        && new_algebraic_notation[0] == current_algebraic_notation[0])
        return 0;

    if (walk_two_houses) {
        if (new_algebraic_notation[1] != '3' && new_algebraic_notation[1] != '4')
            return 0;
    }
    else {
        if (new_position_value > (current_position_value + 1))
            return 0;
    }

    if (new_algebraic_notation[0] != current_algebraic_notation[0]) {
        if (chessboard[chessboard_position_value] > 16)
            return 0;

        if (chessboard[chessboard_position_value] == 0)
            return 0;
    }

    if (new_position_value < current_position_value)
        return 0;

    return 1;
}

int white_bishop_rule(const char *current_algebraic_notation, const char *new_algebraic_notation) {
    if (new_algebraic_notation[0] == current_algebraic_notation[0])
        return 0;

    if (new_algebraic_notation[1] == current_algebraic_notation[1])
        return 0;

    int cont = 0;
    char letter;
    if (new_algebraic_notation[0] > current_algebraic_notation[0]) {
        letter = current_algebraic_notation[0];
        while (letter++ != new_algebraic_notation[0])
            cont++;
    }
    else {
        letter = current_algebraic_notation[0];
        while (letter-- != new_algebraic_notation[0])
            cont++;
    }

    int chessboard_position_value = get_chessboard_position(new_algebraic_notation);
    if (chessboard[chessboard_position_value] > 16)
        return 0;

    int current_position_value = current_algebraic_notation[1] - '0';
    int new_position_value = new_algebraic_notation[1] - '0';

    if (new_position_value == (current_position_value + cont))
        return 1;

    if (new_position_value == (current_position_value - cont))
        return 1;

    return 0;
}

int white_knight_rule(const char *current_algebraic_notation, const char *new_algebraic_notation) {
    int chessboard_position_value = get_chessboard_position(new_algebraic_notation);
    if (chessboard[chessboard_position_value] > 16)
        return 0;

    int current_position_value = current_algebraic_notation[1] - '0';
    int new_position_value = new_algebraic_notation[1] - '0';

    if (new_position_value == (current_position_value + 2) && new_algebraic_notation[0] == (current_algebraic_notation[0] + 1))
        return 1;

    if (new_position_value == (current_position_value + 2) && new_algebraic_notation[0] == (current_algebraic_notation[0] - 1))
        return 1;

    if (new_position_value == (current_position_value - 2) && new_algebraic_notation[0] == (current_algebraic_notation[0] - 1))
        return 1;

    if (new_position_value == (current_position_value - 2) && new_algebraic_notation[0] == (current_algebraic_notation[0] + 1))
        return 1;

    if (new_algebraic_notation[0] == (current_algebraic_notation[0] + 2) && new_position_value == (current_position_value + 1))
        return 1;

    if (new_algebraic_notation[0] == (current_algebraic_notation[0] + 2) && new_position_value == (current_position_value - 1))
        return 1;

    if (new_algebraic_notation[0] == (current_algebraic_notation[0] - 2) && new_position_value == (current_position_value - 1))
        return 1;

    if (new_algebraic_notation[0] == (current_algebraic_notation[0] - 2) && new_position_value == (current_position_value + 1))
        return 1;

    return 0;
}

int white_rook_rule(const char *current_algebraic_notation, const char *new_algebraic_notation) {
    int chessboard_position_value = get_chessboard_position(new_algebraic_notation);
    if (chessboard[chessboard_position_value] > 16)
        return 0;

    int current_position_value = current_algebraic_notation[1] - '0';
    int new_position_value = new_algebraic_notation[1] - '0';

    if (new_position_value != current_position_value && new_algebraic_notation[0] != current_algebraic_notation[0])
        return 0;

    return 1;
}

int white_king_rule(const char *current_algebraic_notation, const char *new_algebraic_notation) {
    int chessboard_position_value = get_chessboard_position(new_algebraic_notation);
    if (chessboard[chessboard_position_value] > 16)
        return 0;

    int current_position_value = current_algebraic_notation[1] - '0';
    int new_position_value = new_algebraic_notation[1] - '0';

    if  (new_position_value == (current_position_value + 1) && new_algebraic_notation[0] == (current_algebraic_notation[0] + 1))
        return 1;

    if  (new_position_value == (current_position_value + 1) && new_algebraic_notation[0] == (current_algebraic_notation[0] - 1))
        return 1;

    if  (new_position_value == (current_position_value - 1) && new_algebraic_notation[0] == (current_algebraic_notation[0] - 1))
        return 1;

    if  (new_position_value == (current_position_value - 1) && new_algebraic_notation[0] == (current_algebraic_notation[0] + 1))
        return 1;

    if  (new_position_value == current_position_value && new_algebraic_notation[0] == (current_algebraic_notation[0] + 1))
        return 1;

    if  (new_position_value == current_position_value && new_algebraic_notation[0] == (current_algebraic_notation[0] - 1))
        return 1;

    if  (new_position_value == (current_position_value + 1) && new_algebraic_notation[0] == current_algebraic_notation[0])
        return 1;

    if  (new_position_value == (current_position_value - 1) && new_algebraic_notation[0] == current_algebraic_notation[0])
        return 1;

    return 0;
}

/* -------------------------------------------------------------------------------------------------------- */

int black_pawn_rule(const char *current_algebraic_notation, const char *new_algebraic_notation) {
    bool walk_two_houses = false;
    if (current_algebraic_notation[1] == '7')
        walk_two_houses = true;

    int current_position_value = current_algebraic_notation[1] - '0';
    int new_position_value = new_algebraic_notation[1] - '0';

    int chessboard_position_value = get_chessboard_position(new_algebraic_notation);

    if (chessboard[chessboard_position_value] > 16 && new_algebraic_notation[0] == current_algebraic_notation[0])
        return 0;

    if (walk_two_houses) {
        if (new_algebraic_notation[1] != '6' && new_algebraic_notation[1] != '5')
            return 0;
    }
    else {
        if (new_position_value < (current_position_value - 1))
            return 0;
    }

    if (new_algebraic_notation[0] != current_algebraic_notation[0]) {
        if (chessboard[chessboard_position_value] < 17 && chessboard[chessboard_position_value] > 0)
            return 0;

        if (chessboard[chessboard_position_value] == 0)
            return 0;
    }

    if (new_position_value > current_position_value)
        return 0;

    return 1;
}

int black_bishop_rule(const char *current_algebraic_notation, const char *new_algebraic_notation) {
    if (new_algebraic_notation[0] == current_algebraic_notation[0])
        return 0;

    if (new_algebraic_notation[1] == current_algebraic_notation[1])
        return 0;

    int cont = 0;
    char letter;
    if (new_algebraic_notation[0] > current_algebraic_notation[0]) {
        letter = current_algebraic_notation[0];
        while (letter++ != new_algebraic_notation[0])
            cont++;
    }
    else {
        letter = current_algebraic_notation[0];
        while (letter-- != new_algebraic_notation[0])
            cont++;
    }

    int chessboard_position_value = get_chessboard_position(new_algebraic_notation);
    if (chessboard[chessboard_position_value] < 17 && chessboard[chessboard_position_value] > 0)
        return 0;

    int current_position_value = current_algebraic_notation[1] - '0';
    int new_position_value = new_algebraic_notation[1] - '0';

    if (new_position_value == (current_position_value + cont))
        return 1;

    if (new_position_value == (current_position_value - cont))
        return 1;

    return 0;
}

int black_knight_rule(const char *current_algebraic_notation, const char *new_algebraic_notation) {
    int chessboard_position_value = get_chessboard_position(new_algebraic_notation);
    if (chessboard[chessboard_position_value] < 17 && chessboard[chessboard_position_value] > 0)
        return 0;

    int current_position_value = current_algebraic_notation[1] - '0';
    int new_position_value = new_algebraic_notation[1] - '0';

    if (new_position_value == (current_position_value + 2) && new_algebraic_notation[0] == (current_algebraic_notation[0] + 1))
        return 1;

    if (new_position_value == (current_position_value + 2) && new_algebraic_notation[0] == (current_algebraic_notation[0] - 1))
        return 1;

    if (new_position_value == (current_position_value - 2) && new_algebraic_notation[0] == (current_algebraic_notation[0] - 1))
        return 1;

    if (new_position_value == (current_position_value - 2) && new_algebraic_notation[0] == (current_algebraic_notation[0] + 1))
        return 1;

    if (new_algebraic_notation[0] == (current_algebraic_notation[0] + 2) && new_position_value == (current_position_value + 1))
        return 1;

    if (new_algebraic_notation[0] == (current_algebraic_notation[0] + 2) && new_position_value == (current_position_value - 1))
        return 1;

    if (new_algebraic_notation[0] == (current_algebraic_notation[0] - 2) && new_position_value == (current_position_value - 1))
        return 1;

    if (new_algebraic_notation[0] == (current_algebraic_notation[0] - 2) && new_position_value == (current_position_value + 1))
        return 1;

    return 0;
}

int black_rook_rule(const char *current_algebraic_notation, const char *new_algebraic_notation) {
    int chessboard_position_value = get_chessboard_position(new_algebraic_notation);
    if (chessboard[chessboard_position_value] < 17 && chessboard[chessboard_position_value] > 0)
        return 0;

    int current_position_value = current_algebraic_notation[1] - '0';
    int new_position_value = new_algebraic_notation[1] - '0';

    if (new_position_value != current_position_value && new_algebraic_notation[0] != current_algebraic_notation[0])
        return 0;

    return 1;
}

int black_king_rule(const char *current_algebraic_notation, const char *new_algebraic_notation) {
    int chessboard_position_value = get_chessboard_position(new_algebraic_notation);
    if (chessboard[chessboard_position_value] < 17 && chessboard[chessboard_position_value] > 0)
        return 0;

    int current_position_value = current_algebraic_notation[1] - '0';
    int new_position_value = new_algebraic_notation[1] - '0';

    if  (new_position_value == (current_position_value + 1) && new_algebraic_notation[0] == (current_algebraic_notation[0] + 1))
        return 1;

    if  (new_position_value == (current_position_value + 1) && new_algebraic_notation[0] == (current_algebraic_notation[0] - 1))
        return 1;

    if  (new_position_value == (current_position_value - 1) && new_algebraic_notation[0] == (current_algebraic_notation[0] - 1))
        return 1;

    if  (new_position_value == (current_position_value - 1) && new_algebraic_notation[0] == (current_algebraic_notation[0] + 1))
        return 1;

    if  (new_position_value == current_position_value && new_algebraic_notation[0] == (current_algebraic_notation[0] + 1))
        return 1;

    if  (new_position_value == current_position_value && new_algebraic_notation[0] == (current_algebraic_notation[0] - 1))
        return 1;

    if  (new_position_value == (current_position_value + 1) && new_algebraic_notation[0] == current_algebraic_notation[0])
        return 1;

    if  (new_position_value == (current_position_value - 1) && new_algebraic_notation[0] == current_algebraic_notation[0])
        return 1;

    return 0;
}