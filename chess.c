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
}

int move_piece(void)
{
    char *i = (char *) malloc(2 * sizeof(char));
    char *an = (char *) malloc(2 * sizeof(char));

    printf("%s: ", turn ? "white" : "black");
    turn = !turn;
    scanf(" %s %s", i, an);

    int iPos;
    for (iPos = 0; iPos < 64; ++iPos)
        if (strcmp(AN[iPos], i) == 0)
            break;

    int anPos;
    for (anPos = 0; anPos < 64; ++anPos)
        if (strcmp(AN[anPos], an) == 0)
            break;

    for (size_t j = 0; j < 64; ++j)
        Cboard[j] = chessboard[j];
    if (rules(iPos, anPos) == 1)
        return 1;

    chessboard[anPos] = chessboard[iPos];
    chessboard[iPos] = 0;
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
            default:
                return 0;
        }
        print_chessboard();
    }
}

int main(void)
{
    system("cls");
    command_line();
    return 0;
}
