#include "chess.h"

void print_chessboard(void)
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

void print_bitboard(void) {
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

int move_piece(void)
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
        Cboard[j] = chessboard[j];

    for (size_t j = 0; j < 64; ++j)
        bitBoard[j] = rules(current, AN[j]);

    if (!bitBoard[newPos])
        return 0;

    chessboard[newPos] = chessboard[currentPos];
    chessboard[currentPos] = 0;
    return 0;
}

void back(Stack *s)
{
    pull(s);
    Node *w = s->top;
    for (size_t i = 0; i < 64; ++i)
        chessboard[i] = w->cb[i];
    turn = !turn;
}

int command_line(void) {
    Stack *s = create();
    print_chessboard();
    push(s, chessboard);

    char *i = (char *) malloc(sizeof(char));
    while (1) {
        printf("\n'h' for help: ");
        scanf(" %c", i);
        switch (i[0]) {
            case 'b':
                back(s);
                break;
            case 'm':
                if (move_piece())
                    continue;
                push(s, chessboard);
                break;
            case 'o':
                output(s);
                continue;
            case 'h':
                puts("https://github.com/leozamboni/chess-engine");
                continue;
            case 'i':
                print_bitboard();
                continue;
            case 'e':
                return 0;
            default:
                continue;
        }
        //system("cls");
        print_chessboard();
    }
}

int main(void)
{
    system("cls");
    command_line();
    return 0;
}
