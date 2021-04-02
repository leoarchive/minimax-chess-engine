#include "rules.h"

int rules(int currentPos, int newPos) {
    if (Cboard[currentPos] > 16 && Cboard[currentPos] < 25)
        if (white_pawn(currentPos, newPos))
            return 1;
    if (Cboard[currentPos] > 8 && Cboard[currentPos] < 17)
        if (black_pawn(currentPos, newPos))
            return 1;
    return 0;
}

int white_pawn(int currentPos, int newPos) {
    char *currentPosChar = (char *) malloc(2 * sizeof(char));
    strcpy(currentPosChar, ANotation[currentPos]);

    bool walkTwoHouses = false;
    if (currentPosChar[1] == '2')
        walkTwoHouses = true;

    char *newPosChar = (char *) malloc(2 * sizeof(char));
    strcpy(newPosChar, ANotation[newPos]);

    int currentPosInt = currentPosChar[1] - '0';
    int newPosInt = newPosChar[1] - '0';

    if (walkTwoHouses) {
        if (newPosChar[1] != '3' && newPosChar[1] != '4') {
            puts("ERROR WHITE PAWN CODE 001");
            return 1;
        }
    }
    else {
        if (newPosInt > (currentPosInt + 1)) {
            puts("ERROR WHITE PAWN CODE 002");
            return 1;
        }
    }

    if (newPosChar[0] != currentPosChar[0]) {
        if (Cboard[newPos] > 17) {
            puts("ERROR WHITE PAWN CODE 003");
            return 1;
        }
        else if (Cboard[newPos] == 0) {
            puts("ERROR WHITE PAWN CODE 004");
            return 1;
        }
    }

    if (newPosInt < currentPosInt) {
        puts("ERROR WHITE PAWN CODE 005");
        return 1;
    }

    return 0;
}

int black_pawn(int currentPos, int newPos) {
    char *currentPosChar = (char *) malloc(2 * sizeof(char));
    strcpy(currentPosChar, ANotation[currentPos]);

    bool walkTwoHouses = false;
    if (currentPosChar[1] == '7')
        walkTwoHouses = true;

    char *newPosChar = (char *) malloc(2 * sizeof(char));
    strcpy(newPosChar, ANotation[newPos]);

    int currentPosInt = currentPosChar[1] - '0';
    int newPosInt = newPosChar[1] - '0';

    if (walkTwoHouses) {
        if (newPosChar[1] != '6' && newPosChar[1] != '5') {
            puts("ERROR BLACK PAWN CODE 001");
            return 1;
        }
    }
    else {
        if (newPosInt < (currentPosInt - 1)) {
            puts("ERROR BLACK PAWN CODE 002");
            return 1;
        }
    }

    if (newPosChar[0] != currentPosChar[0]) {
        if (Cboard[newPos] < 17) {
            puts("ERROR BLACK PAWN CODE 003");
            return 1;
        }
        else if (Cboard[newPos] == 0) {
            puts("ERROR BLACK PAWN CODE 004");
            return 1;
        }
    }

    if (newPosInt > currentPosInt) {
        puts("ERROR BLACK PAWN CODE 005");
        return 1;
    }

    return 0;
}