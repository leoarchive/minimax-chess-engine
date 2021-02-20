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

int notes_coord = 11;
int executed_plays = 0;

void gotoxy(int x, int y);
void enable_ascii_colors_windows(void);

Stack *create_stack(void) {
  Stack *s = (Stack *) malloc(sizeof(Stack));
  s->top = NULL;
  return s;
}

void insert_stack(Stack *s, char *p, char *n, char *c) {
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

void pull_stack(Stack *s, char *p) {
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

Node *get_node(Node *n, char *p, char *c) {
  if (!n)
    return NULL;
  if (strcmp(n->piece, p) == 0 && strcmp(n->color, c) == 0)
    return n;
  else
    return get_node(n->next, p, c);
}

void init_stack(Stack *s) {
  insert_stack(s, "R", "a1", BLACK);
  insert_stack(s, "N", "b1", BLACK);
  insert_stack(s, "B", "c1", BLACK);
  insert_stack(s, "Q", "d1", BLACK);
  insert_stack(s, "K", "e1", BLACK);
  insert_stack(s, "b", "f1", BLACK);
  insert_stack(s, "n", "g1", BLACK);
  insert_stack(s, "r", "h1", BLACK);
  insert_stack(s, "P1", "a2", BLACK);
  insert_stack(s, "P2", "b2", BLACK);
  insert_stack(s, "P3", "c2", BLACK);
  insert_stack(s, "P4", "d2", BLACK);
  insert_stack(s, "P5", "e2", BLACK);
  insert_stack(s, "P6", "f2", BLACK);
  insert_stack(s, "P7", "g2", BLACK);
  insert_stack(s, "P8", "h2", BLACK);
  insert_stack(s, "R", "a8", WHITE);
  insert_stack(s, "N", "b8", WHITE);
  insert_stack(s, "B", "c8", WHITE);
  insert_stack(s, "Q", "d8", WHITE);
  insert_stack(s, "K", "e8", WHITE);
  insert_stack(s, "b", "f8", WHITE);
  insert_stack(s, "n", "g8", WHITE);
  insert_stack(s, "r", "h8", WHITE);
  insert_stack(s, "P1", "a7", WHITE);
  insert_stack(s, "P2", "b7", WHITE);
  insert_stack(s, "P3", "c7", WHITE);
  insert_stack(s, "P4", "d7", WHITE);
  insert_stack(s, "P5", "e7", WHITE);
  insert_stack(s, "P6", "f7", WHITE);
  insert_stack(s, "P7", "g7", WHITE);
  insert_stack(s, "P8", "h7", WHITE);
}

int get_coord(char l) {
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
      return EOF;
  }
}

void print_letters_chessboard(void) {
  char l = 'a';
  while (l != 'i')
    printf(" %c ", l++);
}

void print_chessboard(void) {
  int r = 0, n = r;
  for (size_t i = 0; i < 8; ++i) {
    for (size_t j = 0; j < 8; ++j) {
      if (j % 2 == r)
        printf("%c%c%c", 219, 219, 219);
      else
        printf("%3c", 32);
    }
    printf("%2d\n", ++n);
    r = r == 0 ? 1 : 0;
  }
  print_letters_chessboard();
}

void print_pieces(Stack *s) {
  Node *w = s->top;
  char l;
  int n;
  do {
    l = w->notation[0];
    n = w->notation[1] - '0';
    gotoxy(get_coord(l), n - 1);
    printf("%s%s" RESET, w->color, w->piece);
    w = w->next;
  } while (w);
}

void print_notes(char *p, char *n, char *c) {
  gotoxy(0, notes_coord++);
  printf("%s%s %.2s" RESET, c, p, n);
}

void clear_notes(void) {
  if (notes_coord == 11)
    return;
  do {
    gotoxy(0, --notes_coord);
    printf("%30c", 32);
  } while (notes_coord != 11);
}

void clear_old_move(Stack *s, char *p, char *c) {
  Node *n = get_node(s->top, p, c);
  if (!n)
    return;

  char l = n->notation[0];
  int nb = n->notation[1] - '0';
  int m = (nb - 1) % 2;

  gotoxy(get_coord(l) - 1, nb - 1);
  if (l == 'a' || l == 'c' || l == 'e' || l == 'g') {
    if (m == 0)
      printf("%c%c%c", 219, 219, 219);
    else
      printf("%3c", 32);
  }
  else if (l == 'b' || l == 'd' || l == 'f' || l == 'h') {
    if (m == 0)
      printf("%3c", 32);
    else
      printf("%c%c%c", 219, 219, 219);
  }
}

void back_last_move(Stack *s) {
  if (executed_plays == 0)
    return;
  char *p = s->top->piece;
  char *c = s->top->color;

  clear_old_move(s, p, c);
  pull_stack(s, p);

  Node *n = get_node(s->top, p, c);
  char l = n->notation[0];
  int numb = n->notation[1] - '0';
  gotoxy(get_coord(l), numb - 1);
  printf("%s%s" RESET, n->color, n->piece);

  gotoxy(0, --notes_coord);
  printf("%30c", 32);
  executed_plays--;
}

void execute_move(Stack *s, char *i) {
  char n[2];
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
  c = executed_plays % 2 == 0 ? WHITE : BLACK;
  clear_old_move(s, p, c);

  Node *nd = get_node(s->top, p, c);
  if (!nd)
    return;
  char l = n[0];
  int numb = n[1] - '0';
  gotoxy(get_coord(l), numb - 1);
  printf("%s%s" RESET, nd->color, p);

  insert_stack(s, p, n, c);
  print_notes(p, n, c);
  executed_plays++;
}

void clear_line(void) {
  gotoxy(0, 10);
  printf("%7c", 32);
  gotoxy(0, 10);
}

void move_mode(Stack *s) {
  char i[4];
  while(1) {
    clear_line();
    printf("%c:", executed_plays % 2 == 0 ? 'w' : 'b');
    scanf(" %[^\n]s", i);

    switch (i[0]) {
      case 't':
        return;
      case 'a':
        back_last_move(s);
        break;
      default:
        execute_move(s, i);
    }
  }
}

void init_mode(Stack *s) {
  while(1) {
    clear_line();
    printf(":");

    switch (getchar()) {
      case 'e':
        return;
      case 'm':
        move_mode(s);
        break;
      case 'c':
        clear_notes();
        break;
      default:
        continue;
    }
  }
}

int main(void) {
  system("cls");
  enable_ascii_colors_windows();
  Stack *s = create_stack();
  init_stack(s);
  print_chessboard();
  print_pieces(s);
  init_mode(s);
  return 0;
}

void gotoxy(int x, int y) {
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void enable_ascii_colors_windows(void) {
  DWORD mode;
  GetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), &mode);
  SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), mode |= 0x0004);
}