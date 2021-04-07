#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

Stack *create_stack(void) {
    Stack *s = (Stack *) malloc(sizeof(Stack));
    s->top = NULL;
    return s;
}

void push_stack(Stack *s, const unsigned int cb[]) {
    Node *n = (Node *) malloc(sizeof(Node));
    n->cb = (unsigned int *) malloc(64 * sizeof(unsigned int));
    for (size_t i = 0; i < 64; ++i)
        n->cb[i] = cb[i];
    n->next = s->top;
    s->top = n;
}

void pull_stack(Stack *s) {
    if (s->top->next)
        s->top = s->top->next;
}

void output_stack(Stack *s) {
    Node *w = s->top;
    int j = 0;
    while (w) {
        for (size_t i = 0; i < 64; ++i, ++j) {
            if (j == 8) {
                j = 0;
                puts("");
            }
            printf("%d ", w->cb[i]);
        }
        puts("");
        w = w->next;
    }
}
