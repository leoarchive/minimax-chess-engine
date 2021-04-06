#include "search.c"

int main(void) {
    system(CLEAR);
    command_line();
    return 0;
}

int command_line(void) {
    Stack *s = createStack();
    print_chessboard();
    pushStack(s, chessboard);

    char *i = (char *) malloc(sizeof(char));
    while (1) {
        printf("\n'h' for help: ");
        scanf(" %c", i);
        switch (i[0]) {
            case 'b':
                back_stack(s);
                break;
            case 'm':
                if (move_piece())
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
                print_bitboard();
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
        print_chessboard();
    }
}

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

int move_piece(void) {
    char *current = (char *) malloc(2 * sizeof(char));
    char *new = (char *) malloc(2 * sizeof(char));

    printf("%s: ", turn ? "white" : "black");
    turn = !turn;
    scanf(" %s %s", current, new);
    
    int current_position;
    for (current_position = 0; current_position < 64; ++current_position)
        if (strcmp(AN[current_position], current) == 0)
            break;

    int new_position;
    for (new_position = 0; new_position < 64; ++new_position)
        if (strcmp(AN[new_position], new) == 0)
            break;

    for (size_t j = 0; j < 64; ++j)
        bitboard[j] = move_rules(current, AN[j]);

    //print_bitboard();

    if (bishop_validation(current, new))
        return 0;

    if (!bitboard[new_position])
        return 0;

    chessboard[new_position] = chessboard[current_position];
    chessboard[current_position] = 0;
    return 0;
}

void back_stack(Stack *s) {
    pullStack(s);
    Node *w = s->top;
    for (size_t i = 0; i < 64; ++i)
        chessboard[i] = w->cb[i];
    turn = !turn;
}

int move_rules(const char *current_algebraic_notation, const char *new_algebraic_notation) {
    if (!generic_rule_verify(current_algebraic_notation, new_algebraic_notation))
        return 0;

    int currentChessBPosition = get_chessboard_position(current_algebraic_notation);

    if (chessboard[currentChessBPosition] > 16 && chessboard[currentChessBPosition] < 25)
        return white_pawn_rule(current_algebraic_notation, new_algebraic_notation);

    if (chessboard[currentChessBPosition] == 27 || chessboard[currentChessBPosition] == 30)
        return white_bishop_rule(current_algebraic_notation, new_algebraic_notation);

    if (chessboard[currentChessBPosition] == 26 || chessboard[currentChessBPosition] == 31)
        return white_knight_rule(current_algebraic_notation, new_algebraic_notation);

    if (chessboard[currentChessBPosition] == 25 || chessboard[currentChessBPosition] == 32)
        return white_rook_rule(current_algebraic_notation, new_algebraic_notation);

    if (chessboard[currentChessBPosition] == 28)
        if (!white_rook_rule(current_algebraic_notation, new_algebraic_notation) && !white_bishop_rule(current_algebraic_notation, new_algebraic_notation))
            return 0;

    if (chessboard[currentChessBPosition] == 29)
        return white_king_rule(current_algebraic_notation, new_algebraic_notation);

    /* ----------------------------------------------------------------------------- */

    if (chessboard[currentChessBPosition] > 8 && chessboard[currentChessBPosition] < 17)
        return black_pawn_rule(current_algebraic_notation, new_algebraic_notation);

    if (chessboard[currentChessBPosition] == 3 || chessboard[currentChessBPosition] == 6)
        return black_bishop_rule(current_algebraic_notation, new_algebraic_notation);

    if (chessboard[currentChessBPosition] == 2 || chessboard[currentChessBPosition] == 7)
        return black_knight_rule(current_algebraic_notation, new_algebraic_notation);

    if (chessboard[currentChessBPosition] == 1 || chessboard[currentChessBPosition] == 8)
        return black_rook_rule(current_algebraic_notation, new_algebraic_notation);

    if (chessboard[currentChessBPosition] == 4)
       if (!black_rook_rule(current_algebraic_notation, new_algebraic_notation) && !black_bishop_rule(current_algebraic_notation, new_algebraic_notation))
           return 0;

    if (chessboard[currentChessBPosition] == 5)
        return black_king_rule(current_algebraic_notation, new_algebraic_notation);

    return 1;
}

int get_chessboard_position(const char *pieceAN) {
    for (int pos = 0; pos < 64; ++pos)
        if (strcmp(AN[pos], pieceAN) == 0)
            return pos;
    return 0;
}

int generic_rule_verify(const char *current_algebraic_notation, const char *new_algebraic_notation) {
    if (strcmp(current_algebraic_notation, new_algebraic_notation) == 0)
        return 0;
    return 1;
}

int bishop_validation_verify(char *anlist[], int curr, int new) {
    int k;
    if (curr > new) {
        for (int j = curr; j > new; --j) {
            for (k = 0; k < 64; ++k)
                if (strcmp(AN[k], anlist[j]) == 0)
                    break;
            if (bitboard[k] == 2)
                return 1;
        }
    }
    else {
        for (int j = curr; j < new; ++j) {
            for (k = 0; k < 64; ++k)
                if (strcmp(AN[k], anlist[j]) == 0)
                    break;
            if (bitboard[k] == 2)
                return 1;
        }
    }
    return 0;
}

int bishop_validation(const char *current_algebraic_notation, const char *new_algebraic_notation) {
    int cCBPos = get_chessboard_position(current_algebraic_notation);
    if (chessboard[cCBPos] != 27 && chessboard[cCBPos] != 30
    && chessboard[cCBPos] != 3 && chessboard[cCBPos] != 6)
        return 0;

    char *verAN[] = {"a8","b8","a7","c8","b7","a6","d8","c7",
                     "b6","a5","e8","d7","c6","b5","a4","f8",
                     "e7","d6","c5","b4","a3","g8","f7","e6",
                     "d5","c4","b3","a2","h8","g7","f6","e5",
                     "d4","c3","b2","a1","h7","g6","f5","e4",
                     "d3","c2","b1","h6","g5","f4","e3","d2",
                     "c1","h5","g4","f3","e2","d1","h4","g3",
                     "f2","e1","h3","g2","f1","h2","g1","h1",
                     "h8","g8","h7","f8","g7","h6","e8","f7",
                     "g6","h5","d8","e7","f6","g5","h4","c8",
                     "d7","e6","f5","g4","h3","b8","c7","d6",
                     "e5","f4","g3","h2","a8","b7","c6","d5",
                     "e4","f3","g2","h1","a7","b6","c5","d4",
                     "e3","f2","g1","a6","b5","c4","d3","e2",
                     "f1","a5","b4","c3","d2","e1","a4","b3",
                     "c2","d1","a3","b2","c1","a2","b1","a1"};

    for (int i = 0; i < 128; ++i) {
        if (strcmp(verAN[i], current_algebraic_notation) == 0) {
            for (int j = 0; j < 128; ++j) {
                if (strcmp(verAN[j], new_algebraic_notation) == 0) {
                    if ((j - i) < -8 || (j - i) > 8)
                        continue;
                    else
                        return bishop_validation_verify(verAN, i, j);
                }
            }
        }
    }
    return 0;
}

int white_pawn_rule(const char *current_algebraic_notation, const char *new_algebraic_notation) {
    bool walkTwoHouses = false;
    if (current_algebraic_notation[1] == '2')
        walkTwoHouses = true;

    int currentPosInt = current_algebraic_notation[1] - '0';
    int newPosInt = new_algebraic_notation[1] - '0';

    if (walkTwoHouses) {
        if (new_algebraic_notation[1] != '3' && new_algebraic_notation[1] != '4')
            return 0;
    }
    else {
        if (newPosInt > (currentPosInt + 1))
            return 0;
    }

    int new_algebraic_notationChessBPosition = get_chessboard_position(new_algebraic_notation);

    if (new_algebraic_notation[0] != current_algebraic_notation[0]) {
        if (chessboard[new_algebraic_notationChessBPosition] > 17)
            return 0;

        if (chessboard[new_algebraic_notationChessBPosition] == 0)
            return 0;
    }

    if (newPosInt < currentPosInt)
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

    int chessBPosition = get_chessboard_position(new_algebraic_notation);
    if (chessboard[chessBPosition] > 16)
        return 2;

    int currentPosInt = current_algebraic_notation[1] - '0';
    int newPosInt = new_algebraic_notation[1] - '0';

    if (newPosInt == (currentPosInt + cont))
        return 1;

    if (newPosInt == (currentPosInt - cont))
        return 1;

    return 0;
}

int white_knight_rule(const char *current_algebraic_notation, const char *new_algebraic_notation) {
    int chessBPosition = get_chessboard_position(new_algebraic_notation);
    if (chessboard[chessBPosition] > 16)
        return 0;

    int currentPosInt = current_algebraic_notation[1] - '0';
    int newPosInt = new_algebraic_notation[1] - '0';

    if (newPosInt == (currentPosInt + 2) && new_algebraic_notation[0] == (current_algebraic_notation[0] + 1))
        return 1;

    if (newPosInt == (currentPosInt + 2) && new_algebraic_notation[0] == (current_algebraic_notation[0] - 1))
        return 1;

    if (newPosInt == (currentPosInt - 2) && new_algebraic_notation[0] == (current_algebraic_notation[0] - 1))
        return 1;

    if (newPosInt == (currentPosInt - 2) && new_algebraic_notation[0] == (current_algebraic_notation[0] + 1))
        return 1;

    if (new_algebraic_notation[0] == (current_algebraic_notation[0] + 2) && newPosInt == (currentPosInt + 1))
        return 1;

    if (new_algebraic_notation[0] == (current_algebraic_notation[0] + 2) && newPosInt == (currentPosInt - 1))
        return 1;

    if (new_algebraic_notation[0] == (current_algebraic_notation[0] - 2) && newPosInt == (currentPosInt - 1))
        return 1;

    if (new_algebraic_notation[0] == (current_algebraic_notation[0] - 2) && newPosInt == (currentPosInt + 1))
        return 1;

    return 0;
}

int white_rook_rule(const char *current_algebraic_notation, const char *new_algebraic_notation) {
    int chessBPosition = get_chessboard_position(new_algebraic_notation);
    if (chessboard[chessBPosition] > 16)
        return 0;

    int currentPosInt = current_algebraic_notation[1] - '0';
    int newPosInt = new_algebraic_notation[1] - '0';

    if (newPosInt != currentPosInt && new_algebraic_notation[0] != current_algebraic_notation[0])
        return 0;

    return 1;
}

int white_king_rule(const char *current_algebraic_notation, const char *new_algebraic_notation) {
    int chessBPosition = get_chessboard_position(new_algebraic_notation);
    if (chessboard[chessBPosition] > 16)
        return 0;

    int currentPosInt = current_algebraic_notation[1] - '0';
    int newPosInt = new_algebraic_notation[1] - '0';

    if  (newPosInt == (currentPosInt + 1) && new_algebraic_notation[0] == (current_algebraic_notation[0] + 1))
        return 1;

    if  (newPosInt == (currentPosInt + 1) && new_algebraic_notation[0] == (current_algebraic_notation[0] - 1))
        return 1;

    if  (newPosInt == (currentPosInt - 1) && new_algebraic_notation[0] == (current_algebraic_notation[0] - 1))
        return 1;

    if  (newPosInt == (currentPosInt - 1) && new_algebraic_notation[0] == (current_algebraic_notation[0] + 1))
        return 1;

    if  (newPosInt == currentPosInt && new_algebraic_notation[0] == (current_algebraic_notation[0] + 1))
        return 1;

    if  (newPosInt == currentPosInt && new_algebraic_notation[0] == (current_algebraic_notation[0] - 1))
        return 1;

    if  (newPosInt == (currentPosInt + 1) && new_algebraic_notation[0] == current_algebraic_notation[0])
        return 1;

    if  (newPosInt == (currentPosInt - 1) && new_algebraic_notation[0] == current_algebraic_notation[0])
        return 1;

    return 0;
}

/* ----------------------------------------------------------------------------- */

int black_pawn_rule(const char *current_algebraic_notation, const char *new_algebraic_notation) {
    bool walkTwoHouses = false;
    if (current_algebraic_notation[1] == '7')
        walkTwoHouses = true;

    int currentPosInt = current_algebraic_notation[1] - '0';
    int newPosInt = new_algebraic_notation[1] - '0';

    if (walkTwoHouses) {
        if (new_algebraic_notation[1] != '6' && new_algebraic_notation[1] != '5')
            return 0;
    }
    else {
        if (newPosInt > (currentPosInt - 1))
            return 0;
    }

    int new_algebraic_notationChessBPosition = get_chessboard_position(new_algebraic_notation);

    if (new_algebraic_notation[0] != current_algebraic_notation[0]) {
        if (chessboard[new_algebraic_notationChessBPosition] < 17)
            return 0;
    }

    if (newPosInt > currentPosInt)
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

    int chessBPosition = get_chessboard_position(new_algebraic_notation);
    if (chessboard[chessBPosition] < 16 && chessboard[chessBPosition] > 0)
        return 2;

    int currentPosInt = current_algebraic_notation[1] - '0';
    int newPosInt = new_algebraic_notation[1] - '0';

    if (newPosInt == (currentPosInt + cont))
        return 1;

    if (newPosInt == (currentPosInt - cont))
        return 1;

    return 0;
}

int black_knight_rule(const char *current_algebraic_notation, const char *new_algebraic_notation) {
    int chessBPosition = get_chessboard_position(new_algebraic_notation);
    if (chessboard[chessBPosition] < 16 && chessboard[chessBPosition] > 0)
        return 0;

    int currentPosInt = current_algebraic_notation[1] - '0';
    int newPosInt = new_algebraic_notation[1] - '0';

    if (newPosInt == (currentPosInt + 2) && new_algebraic_notation[0] == (current_algebraic_notation[0] + 1))
        return 1;

    if (newPosInt == (currentPosInt + 2) && new_algebraic_notation[0] == (current_algebraic_notation[0] - 1))
        return 1;

    if (newPosInt == (currentPosInt - 2) && new_algebraic_notation[0] == (current_algebraic_notation[0] - 1))
        return 1;

    if (newPosInt == (currentPosInt - 2) && new_algebraic_notation[0] == (current_algebraic_notation[0] + 1))
        return 1;

    if (new_algebraic_notation[0] == (current_algebraic_notation[0] + 2) && newPosInt == (currentPosInt + 1))
        return 1;

    if (new_algebraic_notation[0] == (current_algebraic_notation[0] + 2) && newPosInt == (currentPosInt - 1))
        return 1;

    if (new_algebraic_notation[0] == (current_algebraic_notation[0] - 2) && newPosInt == (currentPosInt - 1))
        return 1;

    if (new_algebraic_notation[0] == (current_algebraic_notation[0] - 2) && newPosInt == (currentPosInt + 1))
        return 1;

    return 0;
}

int black_rook_rule(const char *current_algebraic_notation, const char *new_algebraic_notation) {
    int chessBPosition = get_chessboard_position(new_algebraic_notation);
    if (chessboard[chessBPosition] < 16 && chessboard[chessBPosition] > 0)
        return 0;

    int currentPosInt = current_algebraic_notation[1] - '0';
    int newPosInt = new_algebraic_notation[1] - '0';

    if (newPosInt != currentPosInt && new_algebraic_notation[0] != current_algebraic_notation[0])
        return 0;

    return 1;
}

int black_king_rule(const char *current_algebraic_notation, const char *new_algebraic_notation) {
    int chessBPosition = get_chessboard_position(new_algebraic_notation);
    if (chessboard[chessBPosition] < 16 && chessboard[chessBPosition] > 0)
        return 0;

    int currentPosInt = current_algebraic_notation[1] - '0';
    int newPosInt = new_algebraic_notation[1] - '0';

    if  (newPosInt == (currentPosInt + 1) && new_algebraic_notation[0] == (current_algebraic_notation[0] + 1))
        return 1;

    if  (newPosInt == (currentPosInt + 1) && new_algebraic_notation[0] == (current_algebraic_notation[0] - 1))
        return 1;

    if  (newPosInt == (currentPosInt - 1) && new_algebraic_notation[0] == (current_algebraic_notation[0] - 1))
        return 1;

    if  (newPosInt == (currentPosInt - 1) && new_algebraic_notation[0] == (current_algebraic_notation[0] + 1))
        return 1;

    if  (newPosInt == currentPosInt && new_algebraic_notation[0] == (current_algebraic_notation[0] + 1))
        return 1;

    if  (newPosInt == currentPosInt && new_algebraic_notation[0] == (current_algebraic_notation[0] - 1))
        return 1;

    if  (newPosInt == (currentPosInt + 1) && new_algebraic_notation[0] == current_algebraic_notation[0])
        return 1;

    if  (newPosInt == (currentPosInt - 1) && new_algebraic_notation[0] == current_algebraic_notation[0])
        return 1;

    return 0;
}