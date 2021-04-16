#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "chess.h"
#include "validation.h"
#include "bitboard.h"

#if defined LINUX || defined __APPLE__
char *pieces[] = {" ",
        "♜","♞","♝","♛","♚","♝","♞","♜",
        "♟","♟","♟","♟","♟","♟","♟","♟",
        "♙","♙","♙","♙","♙","♙","♙","♙",
        "♖","♘","♗","♕","♔","♗","♘","♖"
};
#else
char *pieces[] = {" ",
        "R","N","B","Q","K","B","N","R",
        "P","P","P","P","P","P","P","P",
        "P","P","P","P","P","P","P","P",
        "R","N","B","Q","K","B","N","R"
};
#endif

char *AN[] = {
        "a8","b8","c8","d8","e8","f8","g8","h8",
        "a7","b7","c7","d7","e7","f7","g7","h7",
        "a6","b6","c6","d6","e6","f6","g6","h6",
        "a5","b5","c5","d5","e5","f5","g5","h5",
        "a4","b4","c4","d4","e4","f4","g4","h4",
        "a3","b3","c3","d3","e3","f3","g3","h3",
        "a2","b2","c2","d2","e2","f2","g2","h2",
        "a1","b1","c1","d1","e1","f1","g1","h1"
};

int board[] = {
       1,2,3,4,5,6,7,8,
       9,10,11,12,13,14,15,16,
       0,0,0,0,0,0,0,0,
       0,0,0,0,0,0,0,0,
       0,0,0,0,0,0,0,0,
       0,0,0,0,0,0,0,0,
       17,18,19,20,21,22,23,24,
       25,26,27,28,29,30,31,32
};

bool player = true;

void print_chessboard(void) {
    int j = 0;
    int n = 8;
    bool c = false;
    printf("%d ", n--);
    for (size_t i = 0; i < 64; ++i, ++j) {
        if (j == 8) {
            j = 0;
            puts("");
            printf("%d ", n--);
        }
        else
            c = !c;
        printf("%s", c ? WHITE : BLACK);
        if (board[i] < 17)
            printf("%s ", pieces[board[i]]);
        else
            printf(WHITE_PIECE"%s ", pieces[board[i]]);
        printf(DEFAULT);
    }

    printf("\n  ");

    char l = 'a';
    while (l != 'i')
        printf("%c ", l++);
    puts("");
}

int move(void) {
    char *from = (char *) malloc(2 * sizeof(char));
    char *to = (char *) malloc(2 * sizeof(char));

    printf("%s: ", player ? "white" : "black");
    scanf(" %s %s", from, to);

    int from_pos = get_position(from);
    int to_pos = get_position(to);

    set_bitboard(from);
    if (!bitboard[to_pos]) {
        printf("invalid move");
        return 1;
    }
    if (bitboard[to_pos] && board[to_pos])
        printf("white %s (%s) killed black %s (%s)\n", pieces[board[from_pos]], AN[from_pos], pieces[board[to_pos]], AN[to_pos]);

    board[to_pos] = board[from_pos];
    board[from_pos] = 0;
    SWAP_TURN
    return 0;
}

int get_rules(char *f, char *t) {
    if (strcmp(f, t) == 0)
        return 0;

    from_value = f[1] - '0';
    to_value = t[1] - '0';
    from_char = f[0];
    to_char = t[0];
    to_cb_pos = board[get_position(t)];
    int cb_pos = board[get_position(f)];
    if (!cb_pos)
        return 0;

    if (player) {
        if (cb_pos < 17)
            return 0;
    }
    else {
        if (cb_pos > 16)
            return 0;
    }

    if (cb_pos > 16 && cb_pos < 25 || cb_pos > 8 && cb_pos < 17)
        return pawn();

    if (cb_pos == 27 || cb_pos == 30 || cb_pos == 3 || cb_pos == 6)
        return bishop(f, t);

    if (cb_pos == 26 || cb_pos == 31 || cb_pos == 2 || cb_pos == 7)
        return knight();

    if (cb_pos == 25 || cb_pos == 32 || cb_pos == 1 || cb_pos == 8)
        return rook(f, t);

    if (cb_pos == 28 || cb_pos == 4)
        return queen(f, t);

    if (cb_pos == 29 || cb_pos == 5)
        return king();

    return 1;
}

int get_position(char *p) {
    for (int i = 0; i < 64; ++i)
        if (strcmp(AN[i], p) == 0)
            return i;
    return 0;
}

int pawn(void) {
    bool two_square = false;
    if (player) {
        if (from_value == 2)
            two_square = true;

        if (to_cb_pos && to_cb_pos < 17 && to_char == from_char)
            return 0;

        if (to_value < from_value)
            return 0;
    }
    else {
        if (from_value == 7)
            two_square = true;

        if (to_cb_pos > 16 && to_char == from_char)
            return 0;

        if (to_value > from_value)
            return 0;
    }

    if (two_square) {
        if (player) {
            if (to_value != 3 && to_value != 4)
                return 0;
        }
        else {
            if (to_value != 6 && to_value != 5)
                return 0;
        }
    }
    else {
        if (player) {
            if (to_value > (from_value + 1))
                return 0;
        }
        else {
            if (to_value < (from_value - 1))
                return 0;
        }
    }

    if (to_char != from_char) {
        if (to_char != (from_char + 1) && to_char != (from_char - 1))
            return 0;

        if (from_value == to_value)
            return 0;

        if (player) {
            if (to_cb_pos > 16)
                return 0;

            if (to_value > (from_value + 1))
                return 0;
        }
        else {
            if (to_cb_pos && to_cb_pos < 17)
                return 0;

            if (to_value < (from_value - 1))
                return 0;
        }

        if (to_cb_pos == 0)
            return 0;
    }
    return 1;
}

int bishop(char *f, char *t) {
    if (player) {
        if (to_cb_pos > 16)
            return 0;
    }
    else {
        if (to_cb_pos && to_cb_pos < 17)
            return 0;
    }

    if (to_char == from_char)
        return 0;

    if (to_char == from_char)
        return 0;

    int v = validation(f, t, false);
    int to_pos = get_position(t);
    if (v == 1)
        return 0;
    if (v && v != to_pos)
        return 0;

    int c = 0;
    char l;
    if (to_char > from_char) {
        l = from_char;
        while (l++ != to_char)
            c++;
    }
    else {
        l = from_char;
        while (l-- != to_char)
            c++;
    }

    if (to_value == (from_value + c))
        return 1;

    if (to_value == (from_value - c))
        return 1;

    return 0;
}

int knight(void) {
    if (player) {
        if (to_cb_pos > 16)
            return 0;
    }
    else {
        if (to_cb_pos && to_cb_pos < 17)
            return 0;
    }

    if (to_value == (from_value + 2) && to_char == (from_char + 1))
        return 1;

    if (to_value == (from_value + 2) && to_char == (from_char - 1))
        return 1;

    if (to_value == (from_value - 2) && to_char == (from_char - 1))
        return 1;

    if (to_value == (from_value - 2) && to_char == (from_char + 1))
        return 1;

    if (to_char == (from_char + 2) && to_value == (from_value + 1))
        return 1;

    if (to_char == (from_char + 2) && to_value == (from_value - 1))
        return 1;

    if (to_char == (from_char - 2) && to_value == (from_value - 1))
        return 1;

    if (to_char == (from_char - 2) && to_value == (from_value + 1))
        return 1;

    return 0;
}

int rook(char *f, char *t) {
    if (player) {
        if (to_cb_pos > 16)
            return 0;
    }
    else {
        if (to_cb_pos && to_cb_pos < 17)
            return 0;
    }

    if (to_value != from_value && to_char != from_char)
        return 0;

    int v = validation(f, t, true);
    int to_pos = get_position(t);
    if (v == 1)
        return 0;
    if (v && v != to_pos)
        return 0;

    return 1;
}

int queen(char *f, char *t) {
    if (!rook(f, t) && !bishop(f, t))
        return 0;
    return 1;
}

int king(void) {
    if (player) {
        if (to_cb_pos > 16)
            return 0;
    }
    else {
        if (to_cb_pos && to_cb_pos < 17)
            return 0;
    }

    if  (to_value == (from_value + 1) && to_char == (from_char + 1))
        return 1;

    if  (to_value == (from_value + 1) && to_char == (from_char - 1))
        return 1;

    if  (to_value == (from_value - 1) && to_char == (from_char - 1))
        return 1;

    if  (to_value == (from_value - 1) && to_char == (from_char + 1))
        return 1;

    if  (to_value == from_value && to_char == (from_char + 1))
        return 1;

    if  (to_value == from_value && to_char == (from_char - 1))
        return 1;

    if  (to_value == (from_value + 1) && to_char == from_char)
        return 1;

    if  (to_value == (from_value - 1) && to_char == from_char)
        return 1;

    return 0;
}