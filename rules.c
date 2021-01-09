/* the rules are incomplete but if you can contribute, please! :)
 * https://en.wikipedia.org/wiki/Rules_of_chess */

int rules(List *list, char *piece, char letter, int number) {
    List *current   =   list->next;
    List *died      =   list->next;
    List *ahead     =   list->next;

    while (current) { if (strcmp(current->piece, piece) == 0) break; current = current->next;}

    if (piece[2] == 'w') {
        if (number > current->top->line)
            goto error1;
    } else if (piece[2] == 'b')
        if (number < current->top->line)
            goto error1;

    for (size_t i = current->top->line - 1; i >= number; --i) {
        while (ahead) {
            if (ahead->top->line == i && ahead->top->column == current->top->column)
                goto catch1;
            ahead = ahead->next;
        }
    }

    return 0;
    error1: gotoxy(1, ++historic); printf(RED "Error3: invalid movement for %s" RESET, piece);  return 1;
    catch1: gotoxy(1, ++historic); printf(GREEN "%s captured %s" RESET, piece, died->piece); return 0;
}