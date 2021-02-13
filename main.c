#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define WHITE "\e[0;97m"
#define BLACK "\e[0;90m"
#define RESET "\x1b[0m"

typedef struct node{
    char *piece;
    char *notation;
    char *color;
    struct node *next;
}Node;

typedef struct stack{
    Node *top;
}Stack;

int notesCoordinates = 11;
int executedPlays = 0;

void printChessboard();
void printLettersOnChessboard();
void enableASCIIColorsInWindowsTerminal(void);
int clearMovementNote(void);
Stack *createStack(void);
void gotoxy(int x, int y);
int convertAlgebraicNotationToCoordinates(char l);
void printMovementNotes(char *p, char *n, char *c);
Node *searchNodeOnStack(Node *n, char *p, char *c);
void initiMovementsInStack(Stack *s);
void backLastMovement(Stack *s);
void printPiecesInChessboard(Stack *s);
void movementMode(Stack *s);
void executeMovement(Stack *s, char *i);
void clearLastMovement(Stack *s, char *p, char *c);
void pullStack(Stack *s, char *p);
void insertStack(Stack *s, char *p, char *n, char *c);

int main(void) {
  system("cls");
  enableASCIIColorsInWindowsTerminal();
  Stack *s = createStack();
  char *input = (char *) malloc(1 * sizeof(char));

  initiMovementsInStack(s);
  printChessboard();
  while(1) {
    gotoxy(0, 10);
    printf("%30c", 32);
    gotoxy(0, 10);
    printf(":");
    scanf(" %[^\n]c", input);

    if (strcmp(input, "e") == 0)
      return 0;
    else if (strcmp(input, "s") == 0)
      printPiecesInChessboard(s);
    else if (strcmp(input, "m") == 0)
      movementMode(s);
    else if (strcmp(input, "c") == 0)
      clearMovementNote();
    else
      continue;
  }
}

void printLettersOnChessboard() {
  char l = 'a';
  while (l != 'i')
    printf(" %c ", l++);
}

void printChessboard() {
  int r = 0, n = r;
  for (size_t i = 0; i < 8; ++i) {
    for (size_t j = 0; j < 8; ++j) {
      if (j % 2 == r)
        printf("%c%c%c", 219, 219, 219);
      else
        printf("   ");
    }
    printf(" %d", ++n);
    puts("");
    r = r == 0 ? 1 : 0;
  }
  printLettersOnChessboard();
}

int clearMovementNote(void) {
  gotoxy(0, notesCoordinates);
  printf("%30c", 32);
  if (notesCoordinates == 11)
    return 0;
  notesCoordinates--;
  return clearMovementNote();
}

void printMovementNotes(char *p, char *n, char *c) {
  gotoxy(0, notesCoordinates);
  printf("%s%s %.2s" RESET, c, p, n);
  notesCoordinates++;
}

void printPiecesInChessboard(Stack *s) {
  Node *w = s->top;
  char l;
  int n;
  do {
    l = w->notation[0];
    n = w->notation[1] - '0';
    gotoxy(convertAlgebraicNotationToCoordinates(l), n - 1);
    printf("%s%s" RESET, w->color, w->piece);
    w = w->next;
  } while (w);
}

void pullStack(Stack *s, char *p) {
  Node *n = s->top;
  Node *a = NULL;

  while (n) {
    if (strcmp(n->piece, p) == 0)
      break;
    a = n;
    n = n->next;
  }

  if (!a)
    s->top = n->next;
  else
    a->next = n->next;
}

void clearLastMovement(Stack *s, char *p, char *c) {
  Node *n = searchNodeOnStack(s->top, p, c);
  if (!n)
    return;

  char l = n->notation[0];
  int numb = n->notation[1] - '0';
  int mod = (numb - 1) % 2;

  gotoxy(convertAlgebraicNotationToCoordinates(l) - 1, numb - 1);
  if (mod == 0) {
    if (l == 'a' || l == 'c' || l == 'e' || l == 'g')
      printf("%c%c%c", 219, 219, 219);
    else
      printf("   ");
  }
  else {
    if (l == 'b' || l == 'd' || l == 'f' || l == 'h')
      printf("%c%c%c", 219, 219, 219);
    else
      printf("   ");
  }
}

void executeMovement(Stack *s, char *i) {
  char *n = (char *) malloc(1 * sizeof(char));
  char *p;
  char *c;
  char *v = "KQRrBbNn";
  n[0] = i[3];
  n[1] = i[4];
  for (size_t j = 0; j <= 10; ++j)
    if (i[0] == v[j]) {
      n[0] = i[2];
      n[1] = i[3];
    }
  p = strtok(i, " ");
  c = executedPlays % 2 == 0 ? WHITE : BLACK;

  clearLastMovement(s, p, c);
  Node *nd = searchNodeOnStack(s->top, p, c);
  if (!nd)
    return;

  char l = n[0];
  int numb = n[1] - '0';
  gotoxy(convertAlgebraicNotationToCoordinates(l), numb - 1);
  printf("%s%s" RESET, nd->color, p);

  insertStack(s, p, n, c);
  printMovementNotes(p, n, c);
  executedPlays++;
}

void backLastMovement(Stack *s) {
  if (executedPlays == 0)
    return;
  char *p = s->top->piece;
  char *c = s->top->color;

  clearLastMovement(s, p, c);
  pullStack(s, p);

  Node *n = searchNodeOnStack(s->top, p, c);
  char l = n->notation[0];
  int numb = n->notation[1] - '0';
  gotoxy(convertAlgebraicNotationToCoordinates(l), numb - 1);
  printf("%s%s" RESET, n->color, n->piece);

  gotoxy(0, --notesCoordinates);
  printf("%30c", 32);
  executedPlays--;
}

void movementMode(Stack *s) {
  char *input = (char *) malloc(4 * sizeof(char));

  while(1) {
    gotoxy(0, 10);
    printf("%30c", 32);
    gotoxy(0, 10);
    printf("%c:", executedPlays % 2 == 0 ? 'w' : 'b');
    scanf(" %[^\n]s", input);

    if (input[0] == 'r')
      return;
    else if (input[0] == 'b')
      backLastMovement(s);
    else
      executeMovement(s, input);
  }
}

Node *searchNodeOnStack(Node *n, char *p, char *c) {
  if (!n)
    return NULL;
  if (strcmp(n->piece, p) == 0 && strcmp(n->color, c) == 0)
    return n;
  else
    return searchNodeOnStack(n->next, p, c);
}

Stack *createStack(void) {
  Stack *s = (Stack *) malloc(sizeof(Stack));
  s->top = NULL;
  return s;
}

void insertStack(Stack *s, char *p, char *n, char *c) {
  Node *new = (Node *) malloc(sizeof(Node));
  new->piece = (char *) malloc(1 * sizeof(char));
  new->notation = (char *) malloc(1 * sizeof(char));
  new->color = (char *) malloc(7 * sizeof(char));
  strcpy(new->piece, p);
  strcpy(new->notation, n);
  strcpy(new->color, c);
  new->next = NULL;
  if (s->top)
    new->next = s->top;
  s->top = new;
}

int convertAlgebraicNotationToCoordinates(char l) {
  switch(l) {
    case 'a':
      return 1;
    case 'b':
      return 4;
    case 'c':
      return 7;
    case 'd':
      return 10;
    case 'e':
      return 13;
    case 'f':
      return 16;
    case 'g':
      return 19;
    case 'h':
      return 22;
    default:
      return -0;
  }
}

void initiMovementsInStack(Stack *s) {
  insertStack(s, "R", "a1", BLACK);
  insertStack(s, "N", "b1", BLACK);
  insertStack(s, "B", "c1", BLACK);
  insertStack(s, "Q", "d1", BLACK);
  insertStack(s, "K", "e1", BLACK);
  insertStack(s, "b", "f1", BLACK);
  insertStack(s, "n", "g1", BLACK);
  insertStack(s, "r", "h1", BLACK);
  insertStack(s, "P1", "a2", BLACK);
  insertStack(s, "P2", "b2", BLACK);
  insertStack(s, "P3", "c2", BLACK);
  insertStack(s, "P4", "d2", BLACK);
  insertStack(s, "P5", "e2", BLACK);
  insertStack(s, "P6", "f2", BLACK);
  insertStack(s, "P7", "g2", BLACK);
  insertStack(s, "P8", "h2", BLACK);
  insertStack(s, "R", "a8", WHITE);
  insertStack(s, "N", "b8", WHITE);
  insertStack(s, "B", "c8", WHITE);
  insertStack(s, "Q", "d8", WHITE);
  insertStack(s, "K", "e8", WHITE);
  insertStack(s, "b", "f8", WHITE);
  insertStack(s, "n", "g8", WHITE);
  insertStack(s, "r", "h8", WHITE);
  insertStack(s, "P1", "a7", WHITE);
  insertStack(s, "P2", "b7", WHITE);
  insertStack(s, "P3", "c7", WHITE);
  insertStack(s, "P4", "d7", WHITE);
  insertStack(s, "P5", "e7", WHITE);
  insertStack(s, "P6", "f7", WHITE);
  insertStack(s, "P7", "g7", WHITE);
  insertStack(s, "P8", "h7", WHITE);
}

void gotoxy(int x, int y) {
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void enableASCIIColorsInWindowsTerminal(void) {
  DWORD mode;
  GetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), &mode);
  SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), mode |= 0x0004);
}