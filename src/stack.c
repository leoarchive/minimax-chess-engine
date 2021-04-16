#include <stdlib.h>

#include "stack.h"
#include "chess.h"

Stack *create(void) {
    Stack *s = (Stack *) malloc(sizeof(Stack));
    s->top = NULL;
    return s;
}

void push(Stack *s, const int *cb) {
    Node *n = (Node *) malloc(sizeof(Node));
    n->cb = (int *) malloc(64 * sizeof(int));
    for (size_t i = 0; i < 64; ++i)
        n->cb[i] = cb[i];
    n->next = s->top;
    s->top = n;
}

void pull(Stack *s) {
    if (s->top->next)
        s->top = s->top->next;
}

void back(Stack *s) {
    pull(s);
    Node *w = s->top;
    for (size_t i = 0; i < 64; ++i)
        board[i] = w->cb[i];
    SWAP_TURN
}
