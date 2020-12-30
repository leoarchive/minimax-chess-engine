
# Command line chess in C
Command line chess game written in C for Windows
  | ♜ | ♞ | ♝ | ♛ | ♚ | ♝ | ♞ | ♜ |
  |----|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
  | ♟ | ♟ | ♟ | ♟ | ♟ | ♟ | ♟ | ♟ |
  | a3 | b3 | c3 | d3 | e3 | f3 | g3 | h3 |
  | a4 | b4 | c4 | d4 | e4 | f4 | g4 | h4 |
  | a5 | b5 | c5 | d5 | e5 | f5 | g5 | h5 |
  | a6 | b6 | c6 | d6 | e6 | f6 | g6 | h6 |
 | ♙ | ♙ | ♙ | ♙ | ♙ | ♙ | ♙ | ♙ |
  | ♖ | ♘ | ♗ | ♔ | ♕ | ♗ | ♘ | ♖ |
# Versions
## Version 0.1
* 510 lines.
* Chess game.
* [Chessboard with algebraic notation](https://en.wikipedia.org/wiki/Algebraic_notation_(chess)#:~:text=Algebraic%20notation%20(or%20AN)%20is,books%2C%20magazines%2C%20and%20newspapers.).
* All movements.
* Movement stack list.
* [Incomplete chess rules](https://en.wikipedia.org/wiki/Rules_of_chess)
* Rules only for pawns.
* Death notes only for pawns.

*12/30/2020*
# How to play
## Starting the pieces
for start the pieces in their initial positions on the board type:
> *start*
> 
in normal mode.
## Moviment mode
for make a move type:
> *mov*
> 
 int normal mode. Once entering in moviment mode you remain in movement mode type:
> *back*
> 
to exit and back to the normal mode.
for make a move you first type the name of the piece and the algebraic notation.
*Exemple:*

> *P1w a5*
> 
and type enter.
> P1w<space\>a5<enter\>
> 
*Attention!* 
The name of the piece must be typed as shown on the board and the algebraic notation must always be in lowercase. 
## Pieces and Chessboard
 > Black pieces
 > 
  | ♜ | ♞ | ♝ | ♛ | ♚ | ♝ | ♞ | ♜ |
  |:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
  | ♟ | ♟ | ♟ | ♟ | ♟ | ♟ | ♟ | ♟ |
  | T1b | C1b | B1b | R1b | D1b | B2b | C2b | T2b |
 | P1b | P2b | P3b | P4b | P5b | P6b | P7b | P8b |
  > White pieces
  > 
  | ♙ | ♙ | ♙ | ♙ | ♙ | ♙ | ♙ | ♙ |
  |:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
  | ♖ | ♘ | ♗ | ♔ | ♕ | ♗ | ♘ | ♖ |
  | P1w | P2w | P3w | P4w | P5w | P6w | P7w | P8w |
  | T1w | C1w | B1w | R1w | D1b | B2b | C2b | T2w |
  > Chessboard
  > 
 |  | a | b | c | d | e | f | g | h | 
  |:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
  | 1 | a1 | b1 | c1 | d1 | e1 | f1 | g1 | h1 | 
  | 2 | a2 | b1 | c1 | d1 | e1 | f1 | g1 | h1 |
  | 3 | a3 | b3 | c3 | d3 | e3 | f3 | g3 | h3 |
  | 4 | a4 | b4 | c4 | d4 | e4 | f4 | g4 | h4 |
  | 5 | a5 | b5 | c5 | d5 | e5 | f5 | g5 | h5 |
  | 6 | a6 | b6 | c6 | d6 | e6 | f6 | g6 | h6 |
  | 7 | a7 | b7 | c7 | d7 | e7 | f7 | g7 | h7 |
  | 8 | a8 | b8 | c8 | d8 | e8 | f8 | g8 | h8 |
## Commands
1. *start* start the game create pieces on the board.
2. *mov* motion mode moving pieces.
2.1. *back* back to normal mode.
4. *output* print the movement stack list.
## Modes
* *:* Normal mode.
* *mov:* Moviment mode.

