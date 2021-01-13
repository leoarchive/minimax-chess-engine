#include <windows.h>

#define WHITE 15

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

enum text_modes {
    LASTMODE=-1,
    BW40=0,
    C40,
    BW80,
    C80,
    MONO=7,
    C4350=64
};

text_info vActual = {0, 0, 79, 24, WHITE, WHITE, C80, 25, 80, 1, 1};

void gotoxy(int x, int y)
{
    COORD c;

    if(x < 1 || x > vActual.screenwidth ||
       y < 1 || y > vActual.screenheight) return;
    vActual.curx = x;
    vActual.cury = y;
    c.X = vActual.winleft + x - 1;
    c.Y = vActual.wintop + y - 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}