#include "search.c"

int main(void) {
    system(CLEAR);
    commandLine();
    return 0;
}

int commandLine(void) {
    Stack *s = createStack();
    printChessboard();
    pushStack(s, chessboard);

    char *i = (char *) malloc(sizeof(char));
    while (1) {
        printf("\n'h' for help: ");
        scanf(" %c", i);
        switch (i[0]) {
            case 'b':
                backStack(s);
                break;
            case 'm':
                if (movePiece())
                    continue;
                pushStack(s, chessboard);
                break;
            case 'c':
                outputStack(s);
                continue;
            case 'h':
                puts("https://github.com/leozamboni/dumb-chess-engine");
                continue;
            case 'u':
                printBitboard();
                continue;
            case 'd':
                bpp = 0;
                search();
                continue;
            case 'e':
                return 0;
            default:
                continue;
        }
        //system(CLEAR);
        printChessboard();
    }
}

void printChessboard(void) {
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

void printBitboard(void) {
    size_t j = 0;
    for (size_t i = 0; i < 64; ++i, ++j) {
        if (j == 8) {
            j = 0;
            puts("");
        }
        printf("%d ", bitBoard[i]);
    }
    puts("");
}

int movePiece(void) {
    char *current = (char *) malloc(2 * sizeof(char));
    char *new = (char *) malloc(2 * sizeof(char));

    printf("%s: ", turn ? "white" : "black");
    turn = !turn;
    scanf(" %s %s", current, new);

    int currentPos;
    for (currentPos = 0; currentPos < 64; ++currentPos)
        if (strcmp(AN[currentPos], current) == 0)
            break;

    int newPos;
    for (newPos = 0; newPos < 64; ++newPos)
        if (strcmp(AN[newPos], new) == 0)
            break;

    for (size_t j = 0; j < 64; ++j)
        bitBoard[j] = rules(current, AN[j]);

    printBitboard();

    if (bishopValidation(current, new))
        return 0;

    if (!bitBoard[newPos])
        return 0;

    chessboard[newPos] = chessboard[currentPos];
    chessboard[currentPos] = 0;
    return 0;
}

void backStack(Stack *s) {
    pullStack(s);
    Node *w = s->top;
    for (size_t i = 0; i < 64; ++i)
        chessboard[i] = w->cb[i];
    turn = !turn;
}

int rules(const char *currentAN, const char *newAN) {
    if (!genericRule(currentAN, newAN))
        return 0;

    int currentChessBPosition = getCBPosition(currentAN);

    if (chessboard[currentChessBPosition] > 16 && chessboard[currentChessBPosition] < 25)
        return wPawnRule(currentAN, newAN);

    if (chessboard[currentChessBPosition] == 27 || chessboard[currentChessBPosition] == 30)
        return wBishopRule(currentAN, newAN);

    if (chessboard[currentChessBPosition] == 26 || chessboard[currentChessBPosition] == 31)
        return wKnightRule(currentAN, newAN);

    if (chessboard[currentChessBPosition] == 25 || chessboard[currentChessBPosition] == 32)
        return wRookRule(currentAN, newAN);

    if (chessboard[currentChessBPosition] == 28)
        if (!wRookRule(currentAN, newAN) && !wBishopRule(currentAN, newAN))
            return 0;

    if (chessboard[currentChessBPosition] == 29)
        return wKingRule(currentAN, newAN);

    /* ----------------------------------------------------------------------------- */

    if (chessboard[currentChessBPosition] > 8 && chessboard[currentChessBPosition] < 17)
        return bPawnRule(currentAN, newAN);

    if (chessboard[currentChessBPosition] == 3 || chessboard[currentChessBPosition] == 6)
        return bBishopRule(currentAN, newAN);

    if (chessboard[currentChessBPosition] == 2 || chessboard[currentChessBPosition] == 7)
        return bKnightRule(currentAN, newAN);

    if (chessboard[currentChessBPosition] == 1 || chessboard[currentChessBPosition] == 8)
        return bRookRule(currentAN, newAN);

    if (chessboard[currentChessBPosition] == 4)
       if (!bRookRule(currentAN, newAN) && !bBishopRule(currentAN, newAN))
           return 0;

    if (chessboard[currentChessBPosition] == 5)
        return bKingRule(currentAN, newAN);

    return 1;
}

int getCBPosition(const char *pieceAN) {
    for (int pos = 0; pos < 64; ++pos)
        if (strcmp(AN[pos], pieceAN) == 0)
            return pos;
    return 0;
}

int genericRule(const char *currentAN, const char *newAN) {
    if (strcmp(currentAN, newAN) == 0)
        return 0;
    return 1;
}

int bishopValidationFor(const char *currentAN, const char *newAN, char *anlist[], int cont) {
    int new = 0;
    int curr = 0;
    int i, k;
    for (i = 0; i < cont; ++i)
        if (strcmp(anlist[i], newAN) == 0)
            new = i;
    for (i = 0; i < cont; ++i)
        if (strcmp(anlist[i], currentAN) == 0)
            curr = i;
    if (curr > new) {
        for (int j = curr; j > new; --j) {
            for (k = 0; k < 64; ++k)
                if (strcmp(AN[k], anlist[j]) == 0)
                    break;
            if (bitBoard[k] == 2) {
//                for (i = j; i >= 0; --i) {
//                    for (k = 0; k < 64; ++k)
//                        if (strcmp(AN[k], anlist[i]) == 0)
//                            break;
//                    bitBoard[k] = 0;
//                }
                return 1;
            }
        }
    }
    else {
        for (int j = new; j < curr; ++j) {
            for (k = 0; k < 64; ++k)
                if (strcmp(AN[k], anlist[j]) == 0)
                    break;
            if (bitBoard[k] == 2) {
//                for (i = 0; i <= j; ++i) {
//                    for (k = 0; k < 64; ++k)
//                        if (strcmp(AN[k], anlist[i]) == 0)
//                            break;
//                    bitBoard[k] = 0;
//                }
                return 1;
            }
        }
    }
    return 0;
}

int bishopValidation(const char *currentAN, const char *newAN) {
    int currentChessBPosition = getCBPosition(currentAN);
    if (chessboard[currentChessBPosition] != 27)
        if (chessboard[currentChessBPosition] != 30)
            return 0;

    char *dan[] = {"b8","a7"};
    for (int i = 0; i < 2; ++i)
        if (strcmp(dan[i], currentAN) == 0)
            for (int j = 0; j < 2; ++j)
                if (strcmp(dan[j], newAN) == 0)
                    return bishopValidationFor(currentAN, newAN, dan, 2);

    char *dan2[] = {"c8","b7","a6"};
    for (int i = 0; i < 3; ++i)
        if (strcmp(dan2[i], currentAN) == 0)
            for (int j = 0; j < 3; ++j)
                if (strcmp(dan2[j], newAN) == 0)
                    return bishopValidationFor(currentAN, newAN, dan2, 3);

    char *dan3[] = {"d8","c7","b6","a5"};
    for (int i = 0; i < 4; ++i)
        if (strcmp(dan3[i], currentAN) == 0)
            for (int j = 0; j < 4; ++j)
                if (strcmp(dan3[j], newAN) == 0)
                    return bishopValidationFor(currentAN, newAN, dan3, 4);

    char *dan4[] = {"e8","d7","c6","b5","a4"};
    for (int i = 0; i < 5; ++i)
        if (strcmp(dan4[i], currentAN) == 0)
            for (int j = 0; j < 5; ++j)
                if (strcmp(dan4[j], newAN) == 0)
                    return bishopValidationFor(currentAN, newAN, dan4, 5);

    char *dan5[] = {"f8","e7","d6","c5","b4","a3"};
    for (int i = 0; i < 6; ++i)
        if (strcmp(dan5[i], currentAN) == 0)
            for (int j = 0; j < 6; ++j)
                if (strcmp(dan5[j], newAN) == 0)
                    return bishopValidationFor(currentAN, newAN, dan5, 6);

    char *dan6[] = {"g8","f7","e6","d5","c4","b3","a2"};
    for (int i = 0; i < 7; ++i)
        if (strcmp(dan6[i], currentAN) == 0)
            for (int j = 0; j < 7; ++j)
                if (strcmp(dan6[j], newAN) == 0)
                    return bishopValidationFor(currentAN, newAN, dan6, 7);

    char *dan7[] = {"h8","g7","f6","e5","d4","c3","b2","a1"};
    for (int i = 0; i < 8; ++i)
        if (strcmp(dan7[i], currentAN) == 0)
            for (int j = 0; j < 8; ++j)
                if (strcmp(dan7[j], newAN) == 0)
                    return bishopValidationFor(currentAN, newAN, dan7, 8);

    char *dan8[] = {"h7","g6","f5","e4","d3","c2","b1"};
    for (int i = 0; i < 7; ++i)
        if (strcmp(dan8[i], currentAN) == 0)
            for (int j = 0; j < 7; ++j)
                if (strcmp(dan8[j], newAN) == 0)
                    return bishopValidationFor(currentAN, newAN, dan8, 7);

    char *dan9[] = {"h6","g5","f4","e3","d2","c1"};
    for (int i = 0; i < 6; ++i)
        if (strcmp(dan9[i], currentAN) == 0)
            for (int j = 0; j < 6; ++j)
                if (strcmp(dan9[j], newAN) == 0)
                    return bishopValidationFor(currentAN, newAN, dan9, 6);

    char *dan10[] = {"h5","g4","f3","e2","d1"};
    for (int i = 0; i < 5; ++i)
        if (strcmp(dan10[i], currentAN) == 0)
            for (int j = 0; j < 5; ++j)
                if (strcmp(dan10[j], newAN) == 0)
                    return bishopValidationFor(currentAN, newAN, dan10, 5);

    char *dan11[] = {"h4","g3","f2","e1"};
    for (int i = 0; i < 4; ++i)
        if (strcmp(dan11[i], currentAN) == 0)
            for (int j = 0; j < 4; ++j)
                if (strcmp(dan11[j], newAN) == 0)
                    return bishopValidationFor(currentAN, newAN, dan11, 4);

    char *dan12[] = {"h3","g2","f1"};
    for (int i = 0; i < 3; ++i)
        if (strcmp(dan12[i], currentAN) == 0)
            for (int j = 0; j < 3; ++j)
                if (strcmp(dan12[j], newAN) == 0)
                    return bishopValidationFor(currentAN, newAN, dan12, 3);

    char *dan13[] = {"h2","g1"};
    for (int i = 0; i < 2; ++i)
        if (strcmp(dan13[i], currentAN) == 0)
            for (int j = 0; j < 2; ++j)
                if (strcmp(dan13[j], newAN) == 0)
                    return bishopValidationFor(currentAN, newAN, dan13, 2);

    char *danR[] = {"g8","h7"};
    for (int i = 0; i < 2; ++i)
        if (strcmp(danR[i], currentAN) == 0)
            for (int j = 0; j < 2; ++j)
                if (strcmp(danR[j], newAN) == 0)
                    return bishopValidationFor(currentAN, newAN, danR, 2);

    char *danR2[] = {"f8","g7","h6"};
    for (int i = 0; i < 3; ++i)
        if (strcmp(danR2[i], currentAN) == 0)
            for (int j = 0; j < 3; ++j)
                if (strcmp(danR2[j], newAN) == 0)
                    return bishopValidationFor(currentAN, newAN, danR2, 3);

    char *danR3[] = {"e8","f7","g6","h5"};
    for (int i = 0; i < 4; ++i)
        if (strcmp(danR3[i], currentAN) == 0)
            for (int j = 0; j < 4; ++j)
                if (strcmp(danR3[j], newAN) == 0)
                    return bishopValidationFor(currentAN, newAN, danR3, 4);

    char *danR4[] = {"d8","e7","f6","g5","h4"};
    for (int i = 0; i < 5; ++i)
        if (strcmp(danR4[i], currentAN) == 0)
            for (int j = 0; j < 5; ++j)
                if (strcmp(danR4[j], newAN) == 0)
                    return bishopValidationFor(currentAN, newAN, danR4, 5);

    char *danR5[] = {"c8","d7","e6","f5","g4","h3"};
    for (int i = 0; i < 6; ++i)
        if (strcmp(danR5[i], currentAN) == 0)
            for (int j = 0; j < 6; ++j)
                if (strcmp(danR5[j], newAN) == 0)
                    return bishopValidationFor(currentAN, newAN, danR5, 6);

    char *danR6[] = {"b8","c7","d6","e5","f4","g3","h2"};
    for (int i = 0; i < 7; ++i)
        if (strcmp(danR6[i], currentAN) == 0)
            for (int j = 0; j < 7; ++j)
                if (strcmp(danR6[j], newAN) == 0)
                    return bishopValidationFor(currentAN, newAN, danR6, 7);

    char *danR7[] = {"a8","b7","c6","d5","e4","f3","g2","h1"};
    for (int i = 0; i < 8; ++i)
        if (strcmp(danR7[i], currentAN) == 0)
            for (int j = 0; j < 8; ++j)
                if (strcmp(danR7[j], newAN) == 0)
                    return bishopValidationFor(currentAN, newAN, danR7, 8);

    char *danR8[] = {"a7","b6","c5","d4","e3","f2","g1"};
    for (int i = 0; i < 7; ++i)
        if (strcmp(danR8[i], currentAN) == 0)
            for (int j = 0; j < 7; ++j)
                if (strcmp(danR8[j], newAN) == 0)
                    return bishopValidationFor(currentAN, newAN, danR8, 7);

    char *danR9[] = {"a6","b5","c4","d3","e2","f1"};
    for (int i = 0; i < 6; ++i)
        if (strcmp(danR9[i], currentAN) == 0)
            for (int j = 0; j < 6; ++j)
                if (strcmp(danR9[j], newAN) == 0)
                    return bishopValidationFor(currentAN, newAN, danR9, 6);

    char *danR10[] = {"a5","b4","c3","d2","e1"};
    for (int i = 0; i < 5; ++i)
        if (strcmp(danR10[i], currentAN) == 0)
            for (int j = 0; j < 5; ++j)
                if (strcmp(danR10[j], newAN) == 0)
                    return bishopValidationFor(currentAN, newAN, danR10, 5);

    char *danR11[] = {"a4","b3","c2","d1"};
    for (int i = 0; i < 4; ++i)
        if (strcmp(danR11[i], currentAN) == 0)
            for (int j = 0; j < 4; ++j)
                if (strcmp(danR11[j], newAN) == 0)
                    return bishopValidationFor(currentAN, newAN, danR11, 4);

    char *danR12[] = {"a3","b2","c1"};
    for (int i = 0; i < 3; ++i)
        if (strcmp(danR12[i], currentAN) == 0)
            for (int j = 0; j < 3; ++j)
                if (strcmp(danR12[j], newAN) == 0)
                    return bishopValidationFor(currentAN, newAN, danR12, 3);

    char *danR13[] = {"a2","b1"};
    for (int i = 0; i < 2; ++i)
        if (strcmp(danR13[i], currentAN) == 0)
            for (int j = 0; j < 2; ++j)
                if (strcmp(danR13[j], newAN) == 0)
                    return bishopValidationFor(currentAN, newAN, danR13, 2);

    return 0;
}

int wPawnRule(const char *currentAN, const char *newAN) {
    bool walkTwoHouses = false;
    if (currentAN[1] == '2')
        walkTwoHouses = true;

    int currentPosInt = currentAN[1] - '0';
    int newPosInt = newAN[1] - '0';

    if (walkTwoHouses) {
        if (newAN[1] != '3' && newAN[1] != '4')
            return 0;
    }
    else {
        if (newPosInt > (currentPosInt + 1))
            return 0;
    }

    int newANChessBPosition = getCBPosition(newAN);

    if (newAN[0] != currentAN[0]) {
        if (chessboard[newANChessBPosition] > 17)
            return 0;

        if (chessboard[newANChessBPosition] == 0)
            return 0;
    }

    if (newPosInt < currentPosInt)
        return 0;

    return 1;
}

int wBishopRule(const char *currentAN, const char *newAN) {
    if (newAN[0] == currentAN[0])
        return 0;

    if (newAN[1] == currentAN[1])
        return 0;

    int cont = 0;
    char letter;
    if (newAN[0] > currentAN[0]) {
        letter = currentAN[0];
        while (letter++ != newAN[0])
            cont++;
    }
    else {
        letter = currentAN[0];
        while (letter-- != newAN[0])
            cont++;
    }

    int chessBPosition = getCBPosition(newAN);
    if (chessboard[chessBPosition] > 16)
        return 2;

    int currentPosInt = currentAN[1] - '0';
    int newPosInt = newAN[1] - '0';

    if (newPosInt == (currentPosInt + cont))
        return 1;

    if (newPosInt == (currentPosInt - cont))
        return 1;

    return 0;
}

int wKnightRule(const char *currentAN, const char *newAN) {
    int chessBPosition = getCBPosition(newAN);
    if (chessboard[chessBPosition] > 16)
        return 0;

    int currentPosInt = currentAN[1] - '0';
    int newPosInt = newAN[1] - '0';

    if (newPosInt == (currentPosInt + 2) && newAN[0] == (currentAN[0] + 1))
        return 1;

    if (newPosInt == (currentPosInt + 2) && newAN[0] == (currentAN[0] - 1))
        return 1;

    if (newPosInt == (currentPosInt - 2) && newAN[0] == (currentAN[0] - 1))
        return 1;

    if (newPosInt == (currentPosInt - 2) && newAN[0] == (currentAN[0] + 1))
        return 1;

    if (newAN[0] == (currentAN[0] + 2) && newPosInt == (currentPosInt + 1))
        return 1;

    if (newAN[0] == (currentAN[0] + 2) && newPosInt == (currentPosInt - 1))
        return 1;

    if (newAN[0] == (currentAN[0] - 2) && newPosInt == (currentPosInt - 1))
        return 1;

    if (newAN[0] == (currentAN[0] - 2) && newPosInt == (currentPosInt + 1))
        return 1;

    return 0;
}

int wRookRule(const char *currentAN, const char *newAN) {
    int chessBPosition = getCBPosition(newAN);
    if (chessboard[chessBPosition] > 16)
        return 0;

    int currentPosInt = currentAN[1] - '0';
    int newPosInt = newAN[1] - '0';

    if (newPosInt != currentPosInt && newAN[0] != currentAN[0])
        return 0;

    return 1;
}

int wKingRule(const char *currentAN, const char *newAN) {
    int chessBPosition = getCBPosition(newAN);
    if (chessboard[chessBPosition] > 16)
        return 0;

    int currentPosInt = currentAN[1] - '0';
    int newPosInt = newAN[1] - '0';

    if  (newPosInt == (currentPosInt + 1) && newAN[0] == (currentAN[0] + 1))
        return 1;

    if  (newPosInt == (currentPosInt + 1) && newAN[0] == (currentAN[0] - 1))
        return 1;

    if  (newPosInt == (currentPosInt - 1) && newAN[0] == (currentAN[0] - 1))
        return 1;

    if  (newPosInt == (currentPosInt - 1) && newAN[0] == (currentAN[0] + 1))
        return 1;

    if  (newPosInt == currentPosInt && newAN[0] == (currentAN[0] + 1))
        return 1;

    if  (newPosInt == currentPosInt && newAN[0] == (currentAN[0] - 1))
        return 1;

    if  (newPosInt == (currentPosInt + 1) && newAN[0] == currentAN[0])
        return 1;

    if  (newPosInt == (currentPosInt - 1) && newAN[0] == currentAN[0])
        return 1;

    return 0;
}

/* ----------------------------------------------------------------------------- */

int bPawnRule(const char *currentAN, const char *newAN) {
    bool walkTwoHouses = false;
    if (currentAN[1] == '7')
        walkTwoHouses = true;

    int currentPosInt = currentAN[1] - '0';
    int newPosInt = newAN[1] - '0';

    if (walkTwoHouses) {
        if (newAN[1] != '6' && newAN[1] != '5')
            return 0;
    }
    else {
        if (newPosInt > (currentPosInt - 1))
            return 0;
    }

    int newANChessBPosition = getCBPosition(newAN);

    if (newAN[0] != currentAN[0]) {
        if (chessboard[newANChessBPosition] < 17)
            return 0;
    }

    if (newPosInt > currentPosInt)
        return 0;

    return 1;
}

int bBishopRule(const char *currentAN, const char *newAN) {
    if (newAN[0] == currentAN[0])
        return 0;

    if (newAN[1] == currentAN[1])
        return 0;

    int cont = 0;
    char letter;
    if (newAN[0] > currentAN[0]) {
        letter = currentAN[0];
        while (letter++ != newAN[0])
            cont++;
    }
    else {
        letter = currentAN[0];
        while (letter-- != newAN[0])
            cont++;
    }

    int chessBPosition = getCBPosition(newAN);
    if (chessboard[chessBPosition] < 16 && chessboard[chessBPosition] > 0)
        return 2;

    int currentPosInt = currentAN[1] - '0';
    int newPosInt = newAN[1] - '0';

    if (newPosInt == (currentPosInt + cont))
        return 1;

    if (newPosInt == (currentPosInt - cont))
        return 1;

    return 0;
}

int bKnightRule(const char *currentAN, const char *newAN) {
    int chessBPosition = getCBPosition(newAN);
    if (chessboard[chessBPosition] < 16 && chessboard[chessBPosition] > 0)
        return 0;

    int currentPosInt = currentAN[1] - '0';
    int newPosInt = newAN[1] - '0';

    if (newPosInt == (currentPosInt + 2) && newAN[0] == (currentAN[0] + 1))
        return 1;

    if (newPosInt == (currentPosInt + 2) && newAN[0] == (currentAN[0] - 1))
        return 1;

    if (newPosInt == (currentPosInt - 2) && newAN[0] == (currentAN[0] - 1))
        return 1;

    if (newPosInt == (currentPosInt - 2) && newAN[0] == (currentAN[0] + 1))
        return 1;

    if (newAN[0] == (currentAN[0] + 2) && newPosInt == (currentPosInt + 1))
        return 1;

    if (newAN[0] == (currentAN[0] + 2) && newPosInt == (currentPosInt - 1))
        return 1;

    if (newAN[0] == (currentAN[0] - 2) && newPosInt == (currentPosInt - 1))
        return 1;

    if (newAN[0] == (currentAN[0] - 2) && newPosInt == (currentPosInt + 1))
        return 1;

    return 0;
}

int bRookRule(const char *currentAN, const char *newAN) {
    int chessBPosition = getCBPosition(newAN);
    if (chessboard[chessBPosition] < 16 && chessboard[chessBPosition] > 0)
        return 0;

    int currentPosInt = currentAN[1] - '0';
    int newPosInt = newAN[1] - '0';

    if (newPosInt != currentPosInt && newAN[0] != currentAN[0])
        return 0;

    return 1;
}

int bKingRule(const char *currentAN, const char *newAN) {
    int chessBPosition = getCBPosition(newAN);
    if (chessboard[chessBPosition] < 16 && chessboard[chessBPosition] > 0)
        return 0;

    int currentPosInt = currentAN[1] - '0';
    int newPosInt = newAN[1] - '0';

    if  (newPosInt == (currentPosInt + 1) && newAN[0] == (currentAN[0] + 1))
        return 1;

    if  (newPosInt == (currentPosInt + 1) && newAN[0] == (currentAN[0] - 1))
        return 1;

    if  (newPosInt == (currentPosInt - 1) && newAN[0] == (currentAN[0] - 1))
        return 1;

    if  (newPosInt == (currentPosInt - 1) && newAN[0] == (currentAN[0] + 1))
        return 1;

    if  (newPosInt == currentPosInt && newAN[0] == (currentAN[0] + 1))
        return 1;

    if  (newPosInt == currentPosInt && newAN[0] == (currentAN[0] - 1))
        return 1;

    if  (newPosInt == (currentPosInt + 1) && newAN[0] == currentAN[0])
        return 1;

    if  (newPosInt == (currentPosInt - 1) && newAN[0] == currentAN[0])
        return 1;

    return 0;
}