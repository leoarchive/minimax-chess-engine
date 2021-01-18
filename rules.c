#include "rules.h"

act rules(List *list, char *piece, char letter, int number) {
    if (piece[0] == 'P') {
        if (pawnRules(list, piece, letter, number) == normal)       return normal;
        else if (pawnRules(list, piece, letter, number) == error)   goto error1;
        else goto catch1;
    }
    else if (piece[0] == 'C') {
        if (knightRules(list, piece, letter, number) == normal)     return normal;
        else if (knightRules(list, piece, letter, number) == error) goto error1;
        else goto catch1;
    }
    else if (piece[0] == 'T') {
        if (rookRules(list, piece, letter, number) == normal)       return normal;
        else if (rookRules(list, piece, letter, number) == error)   goto error1;
        else goto catch1;
    }

    error1: gotoxy(1, ++historic); printf(RED "Error3: invalid movement for %s" RESET, piece);  return error;
    catch1: gotoxy(1, ++historic); printf(GREEN "%s captured %s" RESET, piece, catchPiece);     return normal;
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

act knightRules(List *list, char *piece, char letter, int number) {
	List *output    =   list->next;
    List *outputAux =   NULL;
    while (strcmp(output->piece, piece) != 0) output = output->next;

	if (piece[2] == 'w') {
        if (number > output->top->line + 2 || number < output->top->line - 2
        || output->top->line > 8 || output->top->line < 1
        || letter == output->top->column || number == output->top->line) return error;
        else {
            outputAux = list->next;
            while (outputAux) {
                if (outputAux->top->column == letter && outputAux->top->line == number
                && outputAux->piece[2] == 'b') break;
                outputAux = outputAux->next;
            }
            if (!outputAux) return normal;
            else { strcpy(catchPiece, outputAux->piece); return catch;}
        }
	}
	else if (piece[2] == 'b') {
        if (number > output->top->line + 2 || number < output->top->line - 2
        || output->top->line > 8 || output->top->line < 1
        || letter == output->top->column || number == output->top->line) return error;
        else {
            outputAux = list->next;
            while (outputAux) {
                if (outputAux->top->column == letter && outputAux->top->line == number
                    && outputAux->piece[2] == 'w') break;
                outputAux = outputAux->next;
            }
            if (!outputAux) return normal;
            else { strcpy(catchPiece, outputAux->piece); return catch;}
        }
    }

	return normal;
}

act rookRules(List *list, char *piece, char letter, int number) {
    List *output    =   list->next;
    List *outputAux =   NULL;
    while (strcmp(output->piece, piece) != 0) output = output->next;
    int biggest, lowest;

    if (piece[2] == 'w') {
        lowest      =   output->top->line > number ? number : output->top->line;
        biggest     =   output->top->line > number ? output->top->line : number;
        for (size_t i = lowest; i < biggest; ++i) {
            outputAux = list->next;
            while (outputAux) {
                if (outputAux->top->line == i) return error;
                outputAux = outputAux->next;
            }
        }
        if (number != output->top->line || letter != output->top->column) return error;
        else {
            outputAux = list->next;
            while (outputAux) {
                if (outputAux->top->column == letter && outputAux->top->line == number
                    && outputAux->piece[2] == 'b') break;
                outputAux = outputAux->next;
            }
            if (!outputAux) return normal;
            else { strcpy(catchPiece, outputAux->piece); return catch;}
        }
    }

    if (piece[2] == 'b') {
        lowest      =   output->top->line > number ? number : output->top->line;
        biggest     =   output->top->line > number ? output->top->line : number;
        for (size_t i = lowest; i <= biggest; ++i) {
            outputAux = list->next;
            while (outputAux) {
                if (outputAux->top->line == i) return error;
                outputAux = outputAux->next;
            }
        }
        if (number != output->top->line || letter != output->top->column) return error;
        else {
            outputAux = list->next;
            while (outputAux) {
                if (outputAux->top->column == letter && outputAux->top->line == number
                    && outputAux->piece[2] == 'w') break;
                outputAux = outputAux->next;
            }
            if (!outputAux) return normal;
            else { strcpy(catchPiece, outputAux->piece); return catch;}
        }
    }

    return normal;
}