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
#ifndef STACK_H
#define STACK_H

typedef struct node {
    unsigned int *cb;
    struct node *next;
}Node;

typedef struct stack {
    Node *top;
}Stack;

Stack *create_stack(void);
void push_stack(Stack *s, const unsigned int cb[]);
void pull_stack(Stack *s);
void output_stack(Stack *s);

#endif