#include "rules.h"

act rules(List *list, char *piece, char letter, int number) {
    if (piece[0] == 'P') {
        if (pawnRules(list, piece, letter, number) == normal)       return normal;
        else if (pawnRules(list, piece, letter, number) == error)   goto error1;
        else goto catch1;
    }

    error1: gotoxy(1, ++historic); printf(RED "Error3: invalid movement for %s" RESET, piece); return error;
    catch1: gotoxy(1, ++historic); printf(GREEN "%s captured %s" RESET, piece, catchPiece); return normal;
}

act pawnRules(List *list, char *piece, char letter, int number) {
    List *output    =   list->next;
    List *outputAux =   NULL;
    while (strcmp(output->piece, piece) != 0) output = output->next;

    if (piece[2] == 'w') {
        if (letter != output->top->column) {
            outputAux = list->next;
            while (outputAux) {
                if (outputAux->top->column == letter && outputAux->top->line == number
                && outputAux->piece[2] == 'b') break;
                outputAux = outputAux->next;
			}
           	if (!outputAux || number != output->top->line - 1) return error;
            else { strcpy(catchPiece, outputAux->piece); return catch;}
        }
        else if (number != output->top->line - 1 && number != output->top->line - 2
        || output->top->line != 7 && number != output->top->line - 1) return error;
        else {
            output = list->next;
            while (output) {
                if (output->top->column == letter && output->top->line == number) break;
                output = output->next;
            }
            if (output) return error;
            else return normal;
        }
    }
    else if (piece[2] == 'b') {
        if (letter != output->top->column) {
            outputAux = list->next;
            while (outputAux) {
                if (outputAux->top->column == letter && outputAux->top->line == number
                && outputAux->piece[2] == 'w') break;
                outputAux = outputAux->next;
            }
            if (!outputAux || number != output->top->line + 1) return error;
            else { strcpy(catchPiece, outputAux->piece); return catch;}
        }
        else if (output->top->line != 2 && number != output->top->line + 1
        || number != output->top->line + 1 && number != output->top->line + 2) return error;
        else {
            output = list->next;
            while (output) {
                if (output->top->column == letter && output->top->line == number) break;
                output = output->next;
            }
            if (output) return error;
            else return normal;
        }
    }

    return normal;
}
