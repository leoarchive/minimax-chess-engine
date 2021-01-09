
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
[All updates](https://github.com/leozamboni/Chess/blob/master/VERSIONS.md)
# How to play
for start the pieces in their initial positions on the board type:
> *start*
> 
in normal mode.
## Moviment mode
for make a move type:
> *mov*
> 
 in normal mode. Once entering in moviment mode you remain in movement mode type:
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
## Historic
The history is located below the command line, it is responsible for showing the last movements and print of the movement list. In normal mode type
> cls
>
for clear the historic.
## Commands
1. *start* in normal mode, start the game create pieces on the board.
2. *mov* in normal mode, moviment mode moving pieces.
3. *back* in moviment mode, back to normal mode.
4. *output* in normal mode, print the movement stack list.
5. *cls* in normal mode, clear the historic.
## Modes
* *:* Normal mode.
* *mov:* Moviment mode.

