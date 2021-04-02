#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    unsigned int *cb;
    struct node *next;
}Node;

typedef struct stack {
    Node *top;
}Stack;

Stack *create(void);
void push(Stack *s, const unsigned int cb[]);
void pull(Stack *s);
void output(Stack *s);