#include <string.h>

#include "chess.h"

char *diag[] = {
        "a8","b8","a7","c8","b7","a6","d8","c7","b6","a5","e8","d7","c6","b5","a4","f8",
        "e7","d6","c5","b4","a3","g8","f7","e6","d5","c4","b3","a2","h8","g7","f6","e5",
        "d4","c3","b2","a1","h7","g6","f5","e4","d3","c2","b1","h6","g5","f4","e3","d2",
        "c1","h5","g4","f3","e2","d1","h4","g3","f2","e1","h3","g2","f1","h2","g1","h1",
        "h8","g8","h7","f8","g7","h6","e8","f7","g6","h5","d8","e7","f6","g5","h4","c8",
        "d7","e6","f5","g4","h3","b8","c7","d6","e5","f4","g3","h2","a8","b7","c6","d5",
        "e4","f3","g2","h1","a7","b6","c5","d4","e3","f2","g1","a6","b5","c4","d3","e2",
        "f1","a5","b4","c3","d2","e1","a4","b3","c2","d1","a3","b2","c1","a2","b1","a1"
};

char *verhor[] = {
        "a8","b8","c8","d8","e8","f8","g8","h8","a7","b7","c7","d7","e7","f7","g7","h7",
        "a6","b6","c6","d6","e6","f6","g6","h6","a5","b5","c5","d5","e5","f5","g5","h5",
        "a4","b4","c4","d4","e4","f4","g4","h4","a3","b3","c3","d3","e3","f3","g3","h3",
        "a2","b2","c2","d2","e2","f2","g2","h2","a1","b1","c1","d1","e1","f1","g1","h1",
        "a8","a7","a6","a5","a4","a3","a2","a1","b8","b7","b6","b5","b4","b3","b2","b1",
        "c8","c7","c6","c5","c4","c3","c2","c1","d8","d7","d6","d5","d4","d3","d2","d1",
        "e8","e7","e6","e5","e4","e3","e2","e1","f8","f7","f6","f5","f4","f3","f2","f1",
        "g8","g7","g6","g5","g4","g3","g2","g1","h8","h7","h6","h5","h4","h3","h2","h1",
};

int get_validation(char *v[], int f, int t) {
    int k;
    if (f > t) {
        for (int j = f - 1; j > t; --j) {
            for (k = 0; k < 64; ++k)
                if (!strcmp(AN[k], v[j]))
                    break;
            if (player) {
                if (board[k] > BLACKEND)
                    return 1;
                else if (board[k] && board[k] < WHITEINIT)
                    return k;
            }
            if (!player) {
                if (board[k] && board[k] < WHITEINIT)
                    return 1;
                else if (board[k] > BLACKEND)
                    return k;
            }
        }
    }
    else {
        for (int j = f + 1; j < t; ++j) {
            for (k = 0; k < 64; ++k)
                if (!strcmp(AN[k], v[j]))
                    break;
            if (!player) {
                if (board[k] > BLACKEND)
                    return 1;
                else if (board[k] && board[k] < WHITEINIT)
                    return k;
            }
            if (player) {
                if (board[k] && board[k] < WHITEINIT)
                    return 1;
                else if (board[k] > BLACKEND)
                    return k;
            }
        }
    }
    return 0;
}

int validation(char *f, char *t, bool r) {
    if (r) {
        for (int i = 0; i < 128; ++i) {
            if (!strcmp(verhor[i], f)) {
                for (int j = 0; j < 128; ++j) {
                    if (!strcmp(verhor[j], t)) {
                        if ((j - i) < -7 || (j - i) > 7)
                            continue;
                        else
                            return get_validation(verhor, i, j);
                    }
                }
            }
        }
    }
    else {
        for (int i = 0; i < 128; ++i) {
            if (!strcmp(diag[i], f)) {
                for (int j = 0; j < 128; ++j) {
                    if (!strcmp(diag[j], t)) {
                        if ((j - i) < -8 || (j - i) > 8)
                            continue;
                        else
                            return get_validation(diag, i, j);
                    }
                }
            }
        }
    }
    return 0;
}
