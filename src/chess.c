#include "search.c"

int main(void)
{
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
        system(CLEAR);
        printChessboard();
    }
}

void printChessboard(void)
{
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

int movePiece(void)
{
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

    //printBitboard();

    if (!bitBoard[newPos])
        return 0;

    chessboard[newPos] = chessboard[currentPos];
    chessboard[currentPos] = 0;
    return 0;
}

void backStack(Stack *s)
{
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
        if (!wPawnRule(currentAN, newAN))
            return 0;

    if (chessboard[currentChessBPosition] == 27 || chessboard[currentChessBPosition] == 30)
        if (!wBishopRule(currentAN, newAN))
            return 0;

    if (chessboard[currentChessBPosition] == 26 || chessboard[currentChessBPosition] == 31)
        if (!wKnightRule(currentAN, newAN))
            return 0;

    if (chessboard[currentChessBPosition] == 25 || chessboard[currentChessBPosition] == 32)
        if (!wRookRule(currentAN, newAN))
            return 0;

    if (chessboard[currentChessBPosition] == 28)
        if (!wRookRule(currentAN, newAN) && !wBishopRule(currentAN, newAN))
            return 0;

    if (chessboard[currentChessBPosition] == 29)
        if (!wKingRule(currentAN, newAN))
            return 0;

    /* ----------------------------------------------------------------------------- */

    if (chessboard[currentChessBPosition] > 8 && chessboard[currentChessBPosition] < 17)
        if (!bPawnRule(currentAN, newAN))
            return 0;

    if (chessboard[currentChessBPosition] == 3 || chessboard[currentChessBPosition] == 6)
        if (!bBishopRule(currentAN, newAN))
            return 0;

    if (chessboard[currentChessBPosition] == 2 || chessboard[currentChessBPosition] == 7)
        if (!bKnightRule(currentAN, newAN))
            return 0;

    if (chessboard[currentChessBPosition] == 1 || chessboard[currentChessBPosition] == 8)
        if (!bRookRule(currentAN, newAN))
            return 0;

    if (chessboard[currentChessBPosition] == 4)
        if (!bRookRule(currentAN, newAN) && !bBishopRule(currentAN, newAN))
            return 0;

    if (chessboard[currentChessBPosition] == 5)
        if (!bKingRule(currentAN, newAN))
            return 0;

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
        return 0;

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
        return 0;

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