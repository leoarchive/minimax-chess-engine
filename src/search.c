#include "chess.h"

unsigned int bb[64];

int bpp = 0;

const char *search() {
    unsigned int abb[64];
    int bp[] = {wKing,wQueen,wRook,wRookR,wKnight,wKnightR,wBishop,wBishopR,
                wPawn1,wPawn2,wPawn3,wPawn4,wPawn5,wPawn6,wPawn7,wPawn8};
    int bpb[] = {bKing,bQueen,bRook,bRookR,bKnight,bKnightR,bBishop,bBishopR,
                 bPawn1,bPawn2,bPawn3,bPawn4,bPawn5,bPawn6,bPawn7,bPawn8};
    bool no = true;
    int j;
    if (turn) {
        for (j = 0; j < 64; ++j) {
            if (chessboard[j] == bp[bpp])
                break;
        }
        for (int i = 0; i < 64; ++i) {
            bb[i] = rules(AN[j], AN[i]);
            if (bb[i] == 1)
                no = false;
        }
        if (!no) {
            for (int i = 0; i < 64; ++i) {
                if (chessboard[i] < 17 && chessboard[i] > 0) {
                    for (int k = 0; k < 64; ++k) {
                        abb[k] = rules(AN[i], AN[k]);
                        if (abb[k] == 1 && bb[k] == 1) {
                            printf("piece %s goto %s killed by %s\n", AN[j], AN[k], AN[i]);
                            return AN[k];
                        }
                    }
                }
            }
            bpp++;
            return search(turn);
        }
        else {
            bpp++;
            return search(turn);
        }
    }
    else {
        for (j = 0; j < 64; ++j) {
            if (chessboard[j] == bpb[bpp])
                break;
        }
        for (int i = 0; i < 64; ++i) {
            bb[i] = rules(AN[j], AN[i]);
            if (bb[i] == 1)
                no = false;
        }
        if (!no) {
            for (int i = 0; i < 64; ++i) {
                if (chessboard[i] > 16) {
                    for (int k = 0; k < 64; ++k) {
                        abb[k] = rules(AN[i], AN[k]);
                        if (abb[k] == 1 && bb[k] == 1) {
                            printf("piece %s goto %s killed by %s\n", AN[j], AN[k], AN[i]);
                            return AN[k];
                        }
                    }
                }
            }
            bpp++;
            return search(turn);
        }
        else {
            bpp++;
            return search(turn);
        }
    }
}

