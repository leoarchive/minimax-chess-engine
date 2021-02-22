#include <stdio.h>
#include <string.h>

unsigned int chessboard[] = {
	1,2,3,4,5,6,7,8,
	9,10,11,12,13,14,15,16,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	17,18,19,20,21,22,23,24,
	25,26,27,28,29,30,31,32
};

const char *AN[] = {
	"a8","b8","c8","d8","e8","f8","g8","h8",
	"a7","b7","c7","d7","e7","f7","g7","h7",
	"a6","b6","c6","d6","e6","f6","g6","h6",
	"a5","b5","c5","d5","e5","f5","g5","h5",
	"a4","b4","c4","d4","e4","f4","g4","h4",
	"a3","b3","c3","d3","e3","f3","g3","h3",
	"a2","b2","c2","d2","e2","f2","g2","h2",
	"a1","b1","c1","d1","e1","f1","g1","h1"
};

const char *pieces[] = { " ",
	"♜","♞","♝","♛","♚","♝","♞","♜",
	"♟","♟","♟","♟","♟","♟","♟","♟",
	"♙","♙","♙","♙","♙","♙","♙","♙",
	"♖","♘","♗","♕","♔","♗","♘","♖"
};

void print_chessboard(void)
{
	unsigned int j = 0, n = 8, c = 0;
	char l = 'a';
	for (size_t i = 0; i < 64; ++i, ++j) {					
				if (j == 8) {
			j = 0;
			puts("");
		}
		else
			c = c == 0 ? 1 : 0;
		if (!j)
			printf("%d ", n--);
		printf("%s", c == 1 ? "\x1B[43m" : "\x1B[42m");
		printf("%s ", pieces[chessboard[i]]);
		printf("\033[0m");	
	}
	
	printf("\n  ");
	while (l != 'i') {
		printf("%c ", l++);
	}
}

void move_piece(int t) 
{
	char in[4];
	char p[2], an[2];
	size_t i = 0, j = 0;
	printf("\npiece %s\n", t == 1 ? "(1-16)" : "(17-32)");
	scanf(" %[^\n]s", in);
	p = strtok(i, " ");
	an[0] = i[3];
	an[1] = i[4];

	for (; i < 64; ++i)
		if (strcmp(AN[i], p) == 0)
			break;
	printf("piece number: %d\n", chessboard[i]);
	p = chessboard[i];
	chessboard[i] = 0;
	for (; j < 64; ++j) 
		if (strcmp(AN[j], an) == 0)
			break;

	//chessboard[j] = p;
}

int main(void)
{
	int t = 0;
	print_chessboard();
	while (1) {
		move_piece(t);
		print_chessboard();
		t = t == 0 ? 1 : 0;
	}
	puts("");
	return 0;
}
