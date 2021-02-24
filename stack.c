#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	unsigned int *cb;
	struct node *next;
}Node;

typedef struct stack {
	Node *top;
}Stack;

Stack *create(void) 
{
	Stack *s = (Stack *) malloc(sizeof(Stack));
	s->top = NULL;
	return s;
}

void push(Stack *s, unsigned int *cb) 
{
	Node *n = (Node *) malloc(sizeof(Node));
	n->cb = (unsigned int *) malloc(64 * sizeof(unsigned int));
	for (size_t i = 0; i < 64; ++i)
		n->cb[i] = cb[i];
	n->next = s->top;
	s->top = n;
}

void pull(Stack *s) 
{
	if (s->top->next)
		s->top = s->top->next;
}

void output(Stack *s) 
{
	Node *w = s->top;
	while (w) {
		for (size_t i = 0; i < 64; ++i)
			printf("%d ", w->cb[i]);
		puts("");
		w = w->next;
	}
}
