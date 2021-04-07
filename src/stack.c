/*
    Dumb, a chess engine
    Copyright (C) 2021 Leonardo Zamboni

    Dumb is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Dumb is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
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
