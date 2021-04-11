#ifndef SEARCH_H
#define SEARCH_H

int bpp;
unsigned int bb[64];

const char *search(Stack *s);
int move_piece_verify(const char *current, const char *new);

#endif