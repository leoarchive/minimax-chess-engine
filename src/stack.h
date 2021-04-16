#ifndef STACK_H
#define STACK_H

typedef struct node {
    int *cb;
    struct node *next;
}Node;

typedef struct stack {
    Node *top;
}Stack;

Stack *create(void);
void push(Stack *s, const int *cb);
void pull(Stack *s);
void back(Stack *s);

#endif