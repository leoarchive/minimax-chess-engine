#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "stack.c"

#ifdef LINUX
const char *pieces[] = {
        " ",
        "♜","♞","♝","♛","♚","♝","♞","♜",
        "♟","♟","♟","♟","♟","♟","♟","♟",
        "♙","♙","♙","♙","♙","♙","♙","♙",
        "♖","♘","♗","♕","♔","♗","♘","♖"
};
#define CLEAR "clear"
#else
const char *pieces[] = {
        " ",
        "R","N","B","Q","K","B","N","R",
        "P","P","P","P","P","P","P","P",
        "P","P","P","P","P","P","P","P",
        "R","N","B","Q","K","B","N","R"
};
#define CLEAR "cls"
#endif

#define WHT "\e[30;48;5;215m"
#define BLK "\e[30;48;5;208m"

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

enum pieces {empty,bRook,bKnight,bBishop,bQueen,bKing,bBishopR,bKnightR,bRookR,
        bPawn1,bPawn2,bPawn3,bPawn4,bPawn5,bPawn6,bPawn7,bPawn8,
        wPawn1,wPawn2,wPawn3,wPawn4,wPawn5,wPawn6,wPawn7,wPawn8,
        wRook,wKnight,wBishop,wQueen,wKing,wBishopR,wKnightR,wRookR,};

unsigned int chessboard[] = {
        bRook,bKnight,bBishop,bQueen,bKing,bBishopR,bKnightR,bRookR,
        bPawn1,bPawn2,bPawn3,bPawn4,bPawn5,bPawn6,bPawn7,bPawn8,
        empty,empty,empty,empty,empty,empty,empty,empty,
        empty,empty,empty,empty,empty,empty,empty,empty,
        empty,empty,empty,empty,empty,empty,empty,empty,
        empty,empty,empty,empty,empty,empty,empty,empty,
        wPawn1,wPawn2,wPawn3,wPawn4,wPawn5,wPawn6,wPawn7,wPawn8,
        wRook,wKnight,wBishop,wQueen,wKing,wBishopR,wKnightR,wRookR,
};

unsigned int bitBoard[64];

bool turn = true;

int bishopValidation(const char *currentAN, const char *newAN);

void printChessboard(void);
void printBitboard(void);
void backStack(Stack *s);
int movePiece(void);
int commandLine(void);
int rules(const char *currentAN, const char *newAN);
int getCBPosition(const char *pieceAN);
int genericRule(const char *currentAN, const char *newAN);
int wPawnRule(const char *currentAN, const char *newAN);
int wBishopRule(const char *currentAN, const char *newAN);
int wKnightRule(const char *currentAN, const char *newAN);
int wRookRule(const char *currentAN, const char *newAN);
int wKingRule(const char *currentAN, const char *newAN);
int bPawnRule(const char *currentAN, const char *newAN);
int bBishopRule(const char *currentAN, const char *newAN);
int bKnightRule(const char *currentAN, const char *newAN);
int bRookRule(const char *currentAN, const char *newAN);
int bKingRule(const char *currentAN, const char *newAN);