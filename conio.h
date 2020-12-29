#ifndef _CONIO_H_
#define _CONIO_H_

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

#define BLINK 0

typedef
struct text_info {
    unsigned char winleft;        /* left window coordinate */
    unsigned char wintop;         /* top window coordinate */
    unsigned char winright;       /* right window coordinate */
    unsigned char winbottom;      /* bottom window coordinate */
    unsigned char attribute;      /* text attribute */
    unsigned char normattr;       /* normal attribute */
    unsigned char currmode;       /* BW40, BW80, C40, C80, or C4350 */
    unsigned char screenheight;   /* text screen's height */
    unsigned char screenwidth;    /* text screen's width */
    unsigned char curx;           /* x-coordinate in current window */
    unsigned char cury;           /* y-coordinate in current window */
} text_info;

typedef enum {
    BLACK,
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    LIGHTGRAY,
    DARKGRAY,
    LIGHTBLUE,
    LIGHTGREEN,
    LIGHTCYAN,
    LIGHTRED,
    LIGHTMAGENTA,
    YELLOW,
    WHITE
} COLORS;

enum text_modes {
    LASTMODE=-1,
    BW40=0,
    C40,
    BW80,
    C80,
    MONO=7,
    C4350=64
};

#define _NOCURSOR      0
#define _SOLIDCURSOR   1
#define _NORMALCURSOR  2

#define cscanf	scanf

/* Funciones de conio según Borland: */
char *cgets(char *str);
void clreol(void);
void clrscr(void);
int cprintf(const char *format, ...);
int cputs(const char *str);
//int cscanf(char *format, ...);
void delline(void);
int getch(void);
int getche(void);
char *getpass(const char *prompt);
int _gettext(int left, int top, int right, int bottom, void *destin);
void gettextinfo(struct text_info *r);
void gotoxy(int, int);
void highvideo(void);
//inp
//inport
//inportb
//inpw
void insline(void);
int kbhit(void);
void lowvideo(void);
int movetext(int left, int top, int right, int bottom, int destleft, int desttop);
void normvideo(void);
//outp
//outport
//outportb
//outpw
int putch(int c);
int puttext(int left, int top, int right, int bottom, void *source);
void _setcursortype(int cur_t);
void textattr(int newattr);
void textbackground(int newcolor);
void textcolor(int newcolor);
void textmode(int newmode);
int ungetch(int ch);
int wherex(void);
int wherey(void);
void window(int left, int top, int right, int bottom);

#ifdef __cplusplus
}
#endif

#endif /* _CONIO_H_ */