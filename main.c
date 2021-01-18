#include "chess.h"
#include "gotoxy.c"
#include "rules.c"

int main(void) {
    system("cls");

    char *input     =   (char *) malloc(5 * sizeof(char));
    char *inputMov  =   (char *) malloc(6 * sizeof(char));
    char *pieceAux  =   (char *) malloc(3 * sizeof(char));
    char *piece;
    char letter;
    int number;
    List *list = NULL;

    board();
    while (1) {
        gotoxy(1, 10);  printf("%30c\n", 32);
        gotoxy(1, 10);  printf(":");
        scanf(" %[^\n]s", input);

        if (strcmp(input, "exit")           ==  0)      return 0;
        else if (strcmp(input, "start")     ==  0)      list = start();
        else if (strcmp(input, "mov")       ==  0) {
            while (1) {
                gotoxy(1, 10); printf("mov:");
                scanf(" %[^\n]s", inputMov);

                if (strcmp(inputMov, "return")      ==  0)  break;
                else if (strcmp(inputMov, "back")   ==  0)  backMov(list, pieceAux, letter, number);
                else {
                    piece   =   strtok(inputMov, " ");
                    letter  =   inputMov[4];
                    number  =   inputMov[5] - '0';
                    move(list, piece, letter, number);
                    strcpy(pieceAux, piece);
                }
                gotoxy(1, 10); printf("%30c\n", 32);
            }
        }
        else if (strcmp(input, "output")    ==  0)      printList(list);
        else if (strcmp(input, "cls")       ==  0) {
            for (size_t i = 10; i < historic + 1; ++i)  printf("%30c\n", 32); historic = 10;
        }
        else {  gotoxy(1, ++historic); printf(RED "Error0: invalid command" RESET); }
    }
}

List *create(void) {
    List *list  =   (List *) malloc(sizeof(List));
    list->top   =   NULL;
    list->next  =   NULL;
    return      list;
}

List *listInsert(List *list, char *piece) {
    List *newNode   =   (List *) malloc(sizeof(List));
    newNode->piece  =   piece;
    newNode->next   =   list->next;
    newNode->top    =   NULL;
    list->next      =   newNode;
    return          newNode;
}

void stackInsert(List *list, int column, int line) {
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

    gotoxy(1, ++historic);          printf(GREEN "Moviment List\n" RESET);
    while(output != NULL) {
        gotoxy(1, ++historic);      printf("Piece %s\n", output->piece);
        outputNode = output->top;
        while (outputNode != NULL) {
            gotoxy(1, ++historic);  printf("%c%d ", outputNode->column, outputNode->line);
            outputNode = outputNode->next;
        }
        output = output->next;         puts("");
    }

    printf(RED "End\n" RESET);
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

void backMov(List *list, char *piece, char letter, int number) {
    List *output        =   list->next;
    Node *outputNode    =   NULL;

    while (output) {
        outputNode = output->top;
        while (outputNode) {
            if (outputNode->column == letter && outputNode->line == number && strcmp(output->piece, piece) != 0) {
                Convert xy = letterNumberforxy(outputNode->column, outputNode->line);
                gotoxy(xy.column, xy.line); printf("%s", output->piece);
                break;
            }
            outputNode = outputNode->next;
        }
        if (outputNode) break;
        output = output->next;
    }
    if (!output) clearMov(list->next, piece);

    output  = list->next;
    while   (strcmp(output->piece, piece) != 0)     output      =   output->next;
    if      (output->top->next)                     output->top =   output->top->next;
    else    return;
    Convert xy = letterNumberforxy(output->top->column, output->top->line);
    gotoxy(xy.column, xy.line); printf("%s", piece);
}

void clearMov(List *list, char *piece) {
    if (list) {
        if (strcmp(list->piece, piece) == 0) {
            Convert xy    =   letterNumberforxy(list->top->column, list->top->line);
            int letter    =   list->top->column;

            gotoxy(xy.column - 1, xy.line);
            if (xy.line % 2 == 0) {
                if (letter == 'a' || letter == 'c' || letter == 'e' || letter == 'g')
                    printf("%c%c%c%c", 219, 219, 219, 219);
                else    printf("    ");
            } else {
                if (letter == 'b' || letter == 'd' || letter == 'f' || letter == 'h')
                    printf("%c%c%c%c", 219, 219, 219, 219);
                else    printf("    ");
            }
        } else  clearMov(list->next, piece);
    }
}

void move(List *list, char *piece, char letter, int number) {
//    int verify;
    Convert xy = letterNumberforxy(letter, number);

//    verify = rules(list, piece, letter, number);
//    if (!verify) {
//        gotoxy(xy.column, xy.line);     printf("%s", piece);
//        clearMov(list->next, piece);
//        stackInsertOrder(list->next, piece, letter, number);
//    }

    gotoxy(xy.column, xy.line);     printf("%s", piece);
    clearMov(list->next, piece);
    stackInsertOrder(list->next, piece, letter, number);

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

    for (size_t i = 1; i <= 8; ++i)     printf("  %c ", *alphabet++);
    puts("");
}

Convert letterNumberforxy(int letter, int number) {
    Convert xy;

    switch(letter) {
        case 'a':   xy.column   =   4;      break;
        case 'b':   xy.column   =   8;      break;
        case 'c':   xy.column   =   12;     break;
        case 'd':   xy.column   =   16;     break;
        case 'e':   xy.column   =   20;     break;
        case 'f':   xy.column   =   24;     break;
        case 'g':   xy.column   =   28;     break;
        case 'h':   xy.column   =   32;     break;
        default:    gotoxy(1, ++historic); printf(RED "Error1: invalid letter " RESET);
    }
    if      (number > 8 || number < 1) { gotoxy(1, ++historic); printf(RED "Error2: invalid number " RESET); }
    else    xy.line = number;

    return  xy;
}

Convert xyforletterNumber(int x, int y) {
    Convert xy;

    switch(x) {
        case 4:     xy.column   =   'a';    break;
        case 8:     xy.column   =   'b';    break;
        case 12:    xy.column   =   'c';    break;
        case 16:    xy.column   =   'd';    break;
        case 20:    xy.column   =   'e';    break;
        case 24:    xy.column   =   'f';    break;
        case 28:    xy.column   =   'g';    break;
        case 32:    xy.column   =   'h';    break;
        default:    gotoxy(1, ++historic); printf(RED "Error2: invalid number " RESET);
    }
    xy.line = y;

    return    xy;
}

void insertfxy(List *list, int x, int y, char *print) {
    Convert xy = xyforletterNumber(x, y); stackInsert(list, xy.column ,xy.line); gotoxy(x, y); printf("%s", print);
}

List *start(void) {
    List *list = create();

    List *P1w = listInsert(list, "P1w");    insertfxy(P1w, 4, 7, "P1w");
    List *P2w = listInsert(list, "P2w");    insertfxy(P2w, 8, 7, "P2w");
    List *P3w = listInsert(list, "P3w");    insertfxy(P3w, 12, 7, "P3w");
    List *P4w = listInsert(list, "P4w");    insertfxy(P4w, 16, 7, "P4w");
    List *P5w = listInsert(list, "P5w");    insertfxy(P5w, 20, 7, "P5w");
    List *P6w = listInsert(list, "P6w");    insertfxy(P6w, 24, 7, "P6w");
    List *P7w = listInsert(list, "P7w");    insertfxy(P7w, 28, 7, "P7w");
    List *P8w = listInsert(list, "P8w");    insertfxy(P8w, 32, 7, "P8w");
    List *T1w = listInsert(list, "T1w");    insertfxy(T1w, 4, 8, "T1w");
    List *C1w = listInsert(list, "C1w");    insertfxy(C1w, 8, 8, "C1w");
    List *B1w = listInsert(list, "B1w");    insertfxy(B1w, 12, 8, "B1w");
    List *D1w = listInsert(list, "D1w");    insertfxy(D1w, 16, 8, "D1w");
    List *R1w = listInsert(list, "R1w");    insertfxy(R1w, 20, 8, "R1w");
    List *B2w = listInsert(list, "B2w");    insertfxy(B2w, 24, 8, "B2w");
    List *C2w = listInsert(list, "C2w");    insertfxy(C2w, 28, 8, "C2w");
    List *T2w = listInsert(list, "T2w");    insertfxy(T2w, 32, 8, "T2w");
    List *P1b = listInsert(list, "P1b");    insertfxy(P1b, 4, 2, "P1b");
    List *P2b = listInsert(list, "P2b");    insertfxy(P2b, 8, 2, "P2b");
    List *P3b = listInsert(list, "P3b");    insertfxy(P3b, 12, 2, "P3b");
    List *P4b = listInsert(list, "P4b");    insertfxy(P4b, 16, 2, "P4b");
    List *P5b = listInsert(list, "P5b");    insertfxy(P5b, 20, 2, "P5b");
    List *P6b = listInsert(list, "P6b");    insertfxy(P6b, 24, 2, "P6b");
    List *P7b = listInsert(list, "P7b");    insertfxy(P7b, 28, 2, "P7b");
    List *P8b = listInsert(list, "P8b");    insertfxy(P8b, 32, 2, "P8b");
    List *T1b = listInsert(list, "T1b");    insertfxy(T1b, 4, 1, "T1b");
    List *C1b = listInsert(list, "C1b");    insertfxy(C1b, 8, 1, "C1b");
    List *B1b = listInsert(list, "B1b");    insertfxy(B1b, 12, 1, "B1b");
    List *D1b = listInsert(list, "D1b");    insertfxy(D1b, 16, 1, "D1b");
    List *R1b = listInsert(list, "R1b");    insertfxy(R1b, 20, 1, "R1b");
    List *B2b = listInsert(list, "B2b");    insertfxy(B2b, 24, 1, "B2b");
    List *C2b = listInsert(list, "C2b");    insertfxy(C2b, 28, 1, "C2b");
    List *T2b = listInsert(list, "T2b");    insertfxy(T2b, 32, 1, "T2b");

    return list;
}
