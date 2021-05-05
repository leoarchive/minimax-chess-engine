#include <stdio.h>

#include "bitboard.h"
#include "chess.h"

void set_bitboard(char *f) {
    for (size_t i = 0; i < 64; ++i) {
        if (get_rules(f, AN[i]) == 1)
            bitboard[i] = 1;
        else
            bitboard[i] = 0;
    }
}

void print_bitboard(void) {
    for (size_t i = 0; i < 64; ++i) {
        if (i  % 8 == 0) 
            puts("");
        printf("%d ", bitboard[i]);
    }
    puts("");
}
