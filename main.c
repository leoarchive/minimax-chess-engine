#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gotoxy.c"
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define RESET   "\x1b[0m"

int historic    = 10;

typedef struct node {
    int line;
    char column;
    struct node *next;
}Node;

typedef struct list {
    char *piece;
    Node *top;
    struct list *next;
}List;

typedef struct convertxy{
    int line;
    char column;
}Convertxy;

typedef struct convertlinecolumn{
    int line;
    int column;
}ConvertLineColumn;

void clearBuffer(void);
void board(void);
void printList(List *list);
void clearMov(List *list, char *piece);
void stackInsert(List *list, char column, int line);
void move(List *list, char *piece, char letter, int number);
void insertfxy(List *list, int x, int y, char *print);
void stackInsertOrder(List *list, char *piece, char letter, int number);
int rules(List *list, char *piece, char letter, int number);
List *create(void);
List *start(void);
List *listInsert(List *list, char *piece);
ConvertLineColumn letterNumberforxy(char x, int y);
Convertxy xyforletterNumber(int x, int y);

int main(void) {
    system("cls");

    char input[5];
    char inputMov[6];
    char *piece;
    char letter;
    int number;
    List *list = NULL;

    board();
    while (1) {
        gotoxy(1, 10);  printf("              ");
        gotoxy(1, 10);  printf(":");
        scanf("%s", input);
        clearBuffer();

        if (strcmp(input, "exit") == 0)
            return 0;
        else if (strcmp(input, "start") == 0)
            list = start();
        else if (strcmp(input, "mov") == 0){
            do {
                gotoxy(1, 10); printf("mov:");
                scanf("%[^\n]", inputMov);
                clearBuffer();

                if (strcmp(inputMov, "back") == 0)
                    break;

                piece   =   strtok(inputMov, " ");
                letter  =   inputMov[4];
                number  =   inputMov[5] - '0';

                move(list, piece, letter, number);
                gotoxy(1, 10); printf("              ");
            } while (1);
        }
        else if (strcmp(input, "output") == 0) printList(list);
        else { gotoxy(1, ++historic); printf(RED "error: invalid command" RESET); }
    }
}

void clearBuffer(void) {
    int c; while ((c = getchar()) != '\n' && c != EOF);
}

List *create(void) {
    List *list  =   (List *) malloc(sizeof(List));
    list->top   =   NULL;
    list->next  =   NULL;
    return list;
}

List *listInsert(List *list, char *piece) {
    List *newNode   =   (List *) malloc(sizeof(List));
    newNode->piece  =   piece;
    newNode->next   =   list->next;
    newNode->top    =   NULL;
    list->next      =   newNode;
    return newNode;
}

void stackInsert(List *list, char column, int line) {
    Node *newNode       =   (Node *) malloc(sizeof(Node));
    newNode->line       =   line;
    newNode->column     =   column;
    newNode->next       =   NULL;
    if (list->top)
        newNode->next   =   list->top;
    list->top           =   newNode;
}

void printList(List *list) {
    List *output = list->next;
    Node *outputNode;

    while(output != NULL) {
        gotoxy(1, ++historic); printf("Piece %s\n", output->piece);
        outputNode = output->top;
        while (outputNode != NULL) {
            gotoxy(1, ++historic); printf("%c%d\n", outputNode->column, outputNode->line);
            outputNode = outputNode->next;
        }
        output = output->next;
    }
}

void stackInsertOrder(List *list, char *piece, char letter, int number) {
    if (list) {
        if (strcmp(list->piece, piece) == 0) {
            stackInsert(list, letter, number);
            gotoxy(1, ++historic); printf("%s %c%d", piece, letter, number);
        }
        else stackInsertOrder(list->next, piece, letter, number);
    }
}

void clearMov(List *list, char *piece) {
    if (list) {
        if (strcmp(list->piece, piece) == 0) {
            ConvertLineColumn xy    =   letterNumberforxy(list->top->column, list->top->line);
            char letter             =   list->top->column;

            gotoxy(xy.column - 1, xy.line);
            if (xy.line % 2 == 0) {
                if (letter == 'a' || letter == 'c' || letter == 'e' || letter == 'g')
                    printf("%c%c%c%c", 219, 219, 219, 219);
                else
                    printf("    ");
            } else {
                if (letter == 'b' || letter == 'd' || letter == 'f' || letter == 'h')
                    printf("%c%c%c%c", 219, 219, 219, 219);
                else
                    printf("    ");
            }
        } else clearMov(list->next, piece);
    }
}

void move(List *list, char *piece, char letter, int number) {
    int verify;

    ConvertLineColumn xy = letterNumberforxy(letter, number);

    verify = rules(list, piece, letter, number);
    if (!verify) {
        gotoxy(xy.column, xy.line); printf("%s", piece);
        clearMov(list->next, piece);
        stackInsertOrder(list->next, piece, letter, number);
    }

    gotoxy(1, 10);
}

void board(void) {
    char *alphabet      =   "abcdefgh";
    int numbers         =   0;
    int result          =   0;
    size_t width        =   0;
    size_t height       =   0;

    while (height++ < 8) {
        printf("%d ", ++numbers);
        while (width++ < 8) {
            if (width % 2 == result)    printf("%c%c%c%c", 219, 219, 219, 219);
            else                        printf("    ");
        }
        puts("");
        width   =   0;
        result  =   result ? 0 : 1;
    }

    for (size_t i = 1; i <= 8; ++i)
        printf("  %c ", *alphabet++);
    puts("");
}

ConvertLineColumn letterNumberforxy(char x, int y) {
    ConvertLineColumn xy;
    switch(x) {
        case 'a': xy.column =  4; break;
        case 'b': xy.column =  8; break;
        case 'c': xy.column = 12; break;
        case 'd': xy.column = 16; break;
        case 'e': xy.column = 20; break;
        case 'f': xy.column = 24; break;
        case 'g': xy.column = 28; break;
        case 'h': xy.column = 32; break;
        default: gotoxy(1, ++historic); printf(RED "error: invalid letter " RESET);
    }
    if (y > 8 || y < 1) { gotoxy(1, ++historic); printf(RED "error: invalid number " RESET); }
    else xy.line = y;
    return xy;
}

Convertxy xyforletterNumber(int x, int y) {
    Convertxy xy;
    switch(x) {
        case 4: xy.column =  'a'; break;
        case 8: xy.column =  'b'; break;
        case 12: xy.column = 'c'; break;
        case 16: xy.column = 'd'; break;
        case 20: xy.column = 'e'; break;
        case 24: xy.column = 'f'; break;
        case 28: xy.column = 'g'; break;
        case 32: xy.column = 'h'; break;
        default: gotoxy(1, ++historic); printf(RED "error: invalid x cord" RESET);
    }
    xy.line = y;
    return xy;
}

void insertfxy(List *list, int x, int y, char *print) {
    Convertxy xy = xyforletterNumber(x, y); stackInsert(list, xy.column ,xy.line); gotoxy(x, y); printf("%s", print);
}

List *start(void) {
    List *list = create();
    List *P1w = listInsert(list, "P1w"); insertfxy(P1w, 4, 7, "P1w");
    List *P2w = listInsert(list, "P2w"); insertfxy(P2w, 8, 7, "P2w");
    List *P3w = listInsert(list, "P3w"); insertfxy(P3w, 12, 7, "P3w");
    List *P4w = listInsert(list, "P4w"); insertfxy(P4w, 16, 7, "P4w");
    List *P5w = listInsert(list, "P5w"); insertfxy(P5w, 20, 7, "P5w");
    List *P6w = listInsert(list, "P6w"); insertfxy(P6w, 24, 7, "P6w");
    List *P7w = listInsert(list, "P7w"); insertfxy(P7w, 28, 7, "P7w");
    List *P8w = listInsert(list, "P8w"); insertfxy(P8w, 32, 7, "P8w");
    List *T1w = listInsert(list, "T1w"); insertfxy(T1w, 4, 8, "T1w");
    List *C1w = listInsert(list, "C1w"); insertfxy(C1w, 8, 8, "C1w");
    List *B1w = listInsert(list, "B1w"); insertfxy(B1w, 12, 8, "B1w");
    List *D1w = listInsert(list, "D1w"); insertfxy(D1w, 16, 8, "D1w");
    List *R1w = listInsert(list, "R1w"); insertfxy(R1w, 20, 8, "R1w");
    List *B2w = listInsert(list, "B2w"); insertfxy(B2w, 24, 8, "B2w");
    List *C2w = listInsert(list, "C2w"); insertfxy(C2w, 28, 8, "C2w");
    List *T2w = listInsert(list, "T2w"); insertfxy(T2w, 32, 8, "T2w");
    // Black
    List *P1b = listInsert(list, "P1b"); insertfxy(P1b, 4, 2, "P1b");
    List *P2b = listInsert(list, "P2b"); insertfxy(P2b, 8, 2, "P2b");
    List *P3b = listInsert(list, "P3b"); insertfxy(P3b, 12, 2, "P3b");
    List *P4b = listInsert(list, "P4b"); insertfxy(P4b, 16, 2, "P4b");
    List *P5b = listInsert(list, "P5b"); insertfxy(P5b, 20, 2, "P5b");
    List *P6b = listInsert(list, "P6b"); insertfxy(P6b, 24, 2, "P6b");
    List *P7b = listInsert(list, "P7b"); insertfxy(P7b, 28, 2, "P7b");
    List *P8b = listInsert(list, "P8b"); insertfxy(P8b, 32, 2, "P8b");
    List *T1b = listInsert(list, "T1b"); insertfxy(T1b, 4, 1, "T1b");
    List *C1b = listInsert(list, "C1b"); insertfxy(C1b, 8, 1, "C1b");
    List *B1b = listInsert(list, "B1b"); insertfxy(B1b, 12, 1, "B1b");
    List *D1b = listInsert(list, "D1b"); insertfxy(D1b, 16, 1, "D1b");
    List *R1b = listInsert(list, "R1b"); insertfxy(R1b, 20, 1, "R1b");
    List *B2b = listInsert(list, "B2b"); insertfxy(B2b, 24, 1, "B2b");
    List *C2b = listInsert(list, "C2b"); insertfxy(C2b, 28, 1, "C2b");
    List *T2b = listInsert(list, "T2b"); insertfxy(T2b, 32, 1, "T2b");
    return list;
}

int rules(List *list, char *piece, char letter, int number) {
    List *current   =   list->next;
    List *died      =   list->next;
    List *ahead     =   list->next;

    while (current) { if (strcmp(current->piece, piece) == 0) break; current = current->next;}

    if (piece[2] == 'w') {
        if (number > current->top->line)
            goto error1;
    } else if (piece[2] == 'b')
        if (number < current->top->line)
            goto error1;

    for (size_t i = current->top->line - 1; i >= number; --i) {
        while (ahead) {
            if (ahead->top->line == i && ahead->top->column == current->top->column)
                goto error1;
            ahead = ahead->next;
        }
    }

    if (strcmp(piece, "P1w") == 0) {
        if (current->top->column == 'a') {
            if (current->top->line == 7)
                if (letter != 'a' || number < 5 || number > 7)
                    goto error1;
            if (current->top->line < 7)
                if (number != current->top->line - 1)
                    goto error1;
        }
    }

    if (strcmp(piece, "P2w") == 0) {
        if (current->top->column == 'b') {
            if (current->top->line == 7)
                if (letter != 'b' || number < 5 || number > 7)
                    goto error1;
            if (current->top->line < 7)
                if (number != current->top->line - 1)
                    goto error1;
        }
    }

    if (strcmp(piece, "P3w") == 0) {
        if (current->top->column == 'c') {
            if (current->top->line == 7)
                if (letter != 'c' || number < 5 || number > 7)
                    goto error1;
            if (current->top->line < 7)
                if (number != current->top->line - 1)
                    goto error1;
        }
    }

    if (strcmp(piece, "P4w") == 0) {
        if (current->top->column == 'd') {
            if (current->top->line == 7)
                if (letter != 'd' || number < 5 || number > 7)
                    goto error1;
            if (current->top->line < 7)
                if (number != current->top->line - 1)
                    goto error1;
        }
    }

    if (strcmp(piece, "P5w") == 0) {
        if (current->top->column == 'e') {
            if (current->top->line == 7)
                if (letter != 'e' || number < 5 || number > 7)
                    goto error1;
            if (current->top->line < 7)
                if (number != current->top->line - 1)
                    goto error1;
        }
    }

    if (strcmp(piece, "P6w") == 0) {
        if (current->top->column == 'f') {
            if (current->top->line == 7)
                if (letter != 'f' || number < 5 || number > 7)
                    goto error1;
            if (current->top->line < 7)
                if (number != current->top->line - 1)
                    goto error1;
        }
    }

    if (strcmp(piece, "P7w") == 0) {
        if (current->top->column == 'g') {
            if (current->top->line == 7)
                if (letter != 'g' || number < 5 || number > 7)
                    goto error1;
            if (current->top->line < 7)
                if (number != current->top->line - 1)
                    goto error1;
        }
    }

    if (strcmp(piece, "P8w") == 0) {
        if (current->top->column == 'h') {
            if (current->top->line == 7)
                if (letter != 'h' || number < 5 || number > 7)
                    goto error1;
            if (current->top->line < 7)
                if (number != current->top->line - 1)
                    goto error1;
        }
    }

    if (strcmp(piece, "P1b") == 0) {
        if (current->top->column == 'a') {
            if (current->top->line == 2)
                if (letter != 'a' || number > 4 || number < 2)
                    goto error1;
            if (current->top->line > 2)
                if (number != current->top->line + 1)
                    goto error1;
        }
    }

    if (strcmp(piece, "P2b") == 0) {
        if (current->top->column == 'b') {
            if (current->top->line == 2)
                if (letter != 'b' || number > 4 || number < 2)
                    goto error1;
            if (current->top->line > 2)
                if (number != current->top->line + 1)
                    goto error1;
        }
    }

    if (strcmp(piece, "P3b") == 0) {
        if (current->top->column == 'c') {
            if (current->top->line == 2)
                if (letter != 'c' || number > 4 || number < 2)
                    goto error1;
            if (current->top->line > 2)
                if (number != current->top->line + 1)
                    goto error1;
        }
    }

    if (strcmp(piece, "P4b") == 0) {
        if (current->top->column == 'd') {
            if (current->top->line == 2)
                if (letter != 'd' || number > 4 || number < 2)
                    goto error1;
            if (current->top->line > 2)
                if (number != current->top->line + 1)
                    goto error1;
        }
    }

    if (strcmp(piece, "P5b") == 0) {
        if (current->top->column == 'e') {
            if (current->top->line == 2)
                if (letter != 'e' || number > 4 || number < 2)
                    goto error1;
            if (current->top->line > 2)
                if (number != current->top->line + 1)
                    goto error1;
        }
    }

    if (strcmp(piece, "P6b") == 0) {
        if (current->top->column == 'f') {
            if (current->top->line == 2)
                if (letter != 'f' || number > 4 || number < 2)
                    goto error1;
            if (current->top->line > 2)
                if (number != current->top->line + 1)
                    goto error1;
        }
    }

    if (strcmp(piece, "P7b") == 0) {
        if (current->top->column == 'g') {
            if (current->top->line == 2)
                if (letter != 'g' || number > 4 || number < 2)
                    goto error1;
            if (current->top->line > 2)
                if (number != current->top->line + 1)
                    goto error1;
        }
    }

    if (strcmp(piece, "P8b") == 0) {
        if (current->top->column == 'h') {
            if (current->top->line == 2)
                if (letter != 'h' || number > 4 || number < 2)
                    goto error1;
            if (current->top->line > 2)
                if (number != current->top->line + 1)
                    goto error1;
        }
    }

    char key[8] = "abcdefgh";
    char AorH[2] = "bg";
    size_t j;

    for (size_t i = 0; i <= 8; ++i) {
        if (current->top->column == key[i]) {
            if (key[i] == key[0] || key[i] == key[7]) {
                j = key[i] == key[0] ? 0 : 1;
                while (died) {
                    if (died->top->column == AorH[j] && died->top->line == current->top->line - 1)
                        if (letter == AorH[j] && number == died->top->line) goto catch1;
                    died = died->next;
                }
            }
            else {
                while (died) {
                    if (died->top->column == key[i - 1] && died->top->line == current->top->line - 1 ||
                        died->top->column == key[i + 1] && died->top->line == current->top->line - 1)
                        if (letter == key[i - 1] || letter == key[i + 1]) if (number == died->top->line) goto catch1;
                    died = died->next;
                }
                if (letter != key[i]) goto error1;
            }
        }
    }

    return 0;
    error1: gotoxy(1, ++historic); printf(RED "error: invalid movement for %s" RESET, piece);  return 1;
    catch1: gotoxy(1, ++historic); printf(GREEN "%s killed %s" RESET, piece, died->piece); return 0;
}