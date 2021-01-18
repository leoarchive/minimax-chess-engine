/* the rules are incomplete but if you can contribute, please! :)
 * https://github.com/leozamboni/Chess
 * https://en.wikipedia.org/wiki/Rules_of_chess */
#define normal   0
#define error    1
#define catch    2

typedef int act;

char catchPiece[3];

act rules(List *list, char *piece, char letter, int number);
act pawnRules(List *list, char *piece, char letter, int number);