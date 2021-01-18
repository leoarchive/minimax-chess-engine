/* Hey, come on! https://github.com/leozamboni/Chess */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define RESET   "\x1b[0m"

int historic    =   10;

typedef struct node {
    int line;
    int column;
    char *piece;
    struct node *next;
}Node;

typedef struct list {
    char *piece;
    Node *top;
    struct list *next;
}List;

typedef struct convert{
    int line;
    int column;
}Convert;

void board(void);
void printList(List *list);
void printStack(Node *stack);
void clearMov(List *list, char *piece);
void backMov(List *list, List *stack);
void stackInsert(List *list, int column, int line, char *piece);
void insertfxy(List *list, int x, int y, char *print);
void stackInsertOrder(List *list, char *piece, char letter, int number);
void move(List *list, List *stack, char *piece, char letter, int number);
List *create(void);
List *start(void);
List *listInsert(List *list, char *piece);
Convert letterNumberforxy(int letter, int number);
Convert xyforletterNumber(int x, int y);