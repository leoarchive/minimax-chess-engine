#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int *cb;
    struct node *next;
}Node;

typedef struct stack {
    Node *top;
}Stack;

Stack *create_stack(void);
void push_stack(Stack *s, int cb[]);
void pull_stack(Stack *s);
void output_stack(Stack *s);

#endif