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

int annot = 11;
int plays = 0;

void gotoxy(int x, int y) {
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void consoleMode(void) {
  DWORD mode;
  GetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), &mode);
  SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), mode |= 0x0004);
}

Stack *create(void) {
  Stack *s = (Stack *) malloc(sizeof(Stack));
  s->top = NULL;
  return s;
}

void insert(Stack *s, char *p, char *n, char *c) {
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

int board(int cnt, int result, int end) {
  if (end == 8)
    return 0;
  if (cnt == 8) {
    puts("");
    cnt = 0;
    result = result == 1 ? 0 : 1;
    return board(cnt, result, ++end);
  }
  if (cnt % 2 == result)
    printf("%c%c%c", 219, 219, 219);
  else
    printf("   ");
  return board(++cnt, result, end);
}

void init(Stack *s) {
  insert(s, "R", "a1", BLACK);
  insert(s, "N", "b1", BLACK);
  insert(s, "B", "c1", BLACK);
  insert(s, "Q", "d1", BLACK);
  insert(s, "K", "e1", BLACK);
  insert(s, "b", "f1", BLACK);
  insert(s, "n", "g1", BLACK);
  insert(s, "r", "h1", BLACK);
  insert(s, "P1", "a2", BLACK);
  insert(s, "P2", "b2", BLACK);
  insert(s, "P3", "c2", BLACK);
  insert(s, "P4", "d2", BLACK);
  insert(s, "P5", "e2", BLACK);
  insert(s, "P6", "f2", BLACK);
  insert(s, "P7", "g2", BLACK);
  insert(s, "P8", "h2", BLACK);
  insert(s, "R", "a8", WHITE);
  insert(s, "N", "b8", WHITE);
  insert(s, "B", "c8", WHITE);
  insert(s, "Q", "d8", WHITE);
  insert(s, "K", "e8", WHITE);
  insert(s, "b", "f8", WHITE);
  insert(s, "n", "g8", WHITE);
  insert(s, "r", "h8", WHITE);
  insert(s, "P1", "a7", WHITE);
  insert(s, "P2", "b7", WHITE);
  insert(s, "P3", "c7", WHITE);
  insert(s, "P4", "d7", WHITE);
  insert(s, "P5", "e7", WHITE);
  insert(s, "P6", "f7", WHITE);
  insert(s, "P7", "g7", WHITE);
  insert(s, "P8", "h7", WHITE);
}

int convert(char l) {
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

void printPieces(Stack *s) {
  Node *w = s->top;
  char l;
  int n;
  do {
    l = w->notation[0];
    n = w->notation[1] - '0';
    gotoxy(convert(l), n - 1);
    printf("%s%s" RESET, w->color, w->piece);
    w = w->next;
  } while (w);
}

void numberBoard(int n) {
  if (n > 8)
    return;
  gotoxy(25, n - 1);
  if (n)
    printf("%d", n);
  numberBoard(++n);
}

void letterBoard(char *l, size_t i) {
  if (i == 8)
    return;
  printf(" %c ", *l++);
  letterBoard(l, ++i);
}

Node *search(Stack *s, char *p, char *c) {
  Node *w = s->top;
  while (w) {
    if (strcmp(w->piece, p) == 0 && strcmp(w->color, c) == 0)
      return w;
    w = w->next;
  }
  return NULL;
}

void clsMov(Stack *s, char *p, char *c) {
  Node *result = search(s, p, c);
  char l = result->notation[0];
  int numb = result->notation[1] - '0';
  int mod = (numb - 1) % 2;
  gotoxy(convert(l) - 1, numb - 1);
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

void clsAnnot(int i) {
  gotoxy(0, i);
  printf("%30c", 32);
  if (i == annot) {
    annot = 11;
    return;
  }
  i++;
  clsAnnot(i);
}

void annotation(char *p, char *n, char *c) {
  gotoxy(0, annot);
  printf("%s%s %c%c" RESET, c, p, n[0], n[1]);
  annot++;
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

void backMov(Stack *s) {
  if (plays == 0)
    return;
  clsMov(s, s->top->piece, s->top->color);
  char *p = s->top->piece;
  char *c = s->top->color;
  pullStack(s, s->top->piece);
  Node *n = search(s, p, c);
  char l = n->notation[0];
  int numb = n->notation[1] - '0';
  gotoxy(convert(l), numb - 1);
  printf("%s%s" RESET, n->color, n->piece);
  plays--;
}

void makeMov(Stack *s, char *p, char *n, char *c) {
  clsMov(s, p, c);
  Node *result = search(s, p, c);
  char l = n[0];
  int numb = n[1] - '0';
  gotoxy(convert(l), numb - 1);
  printf("%s%s" RESET, result->color, p);
  insert(s, p, n, c);
  annotation(p, n, c);
  plays++;
}

void movMode(Stack *s) {
  char *input = (char *) malloc(4 * sizeof(char));
  char *n = (char *) malloc(1 * sizeof(char));
  char *p;
  char *c = WHITE;

  while(1) {
    gotoxy(0, 10);
    printf("%30c", 32);
    gotoxy(0, 10);
    if (strcmp(c, WHITE) == 0)
      printf("w:");
    else
      printf("b:");
    scanf(" %[^\n]s", input);

    if (input[0] == 'r')
      return;
    else if (input[0] == 'b') {
      backMov(s);
      continue;
    }
    else {
      p = strtok(input, " ");
      n[0] = input[3];
      n[1] = input[4];
      makeMov(s, p, n, c);
      c = strcmp(c, WHITE) == 0 ? BLACK : WHITE;
    }
  }
}

int main(void) {
  system("cls");
  consoleMode();
  Stack *s = create();
  char *input = (char *) malloc(1 * sizeof(char));

  init(s);
  board(0, 0, 0);
  letterBoard("abcdefgh", 0);
  numberBoard(0);
  while(1) {
    gotoxy(0, 10);
    printf("%30c", 32);
    gotoxy(0, 10);
    printf(":");
    scanf(" %[^\n]c", input);

    if (strcmp(input, "e") == 0)
      return 0;
    else if (strcmp(input, "s") == 0)
      printPieces(s);
    else if (strcmp(input, "m") == 0)
      movMode(s);
    else if (strcmp(input, "c") == 0)
      clsAnnot(11);
    else
      continue;
  }
}