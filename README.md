# Command line chess in C
Command line chess game written in C for Windows
# Versions
## Version 0.1
*12/30/2020*
* 510 lines.
* Chess game.
* [Chessboard with algebraic notation](https://en.wikipedia.org/wiki/Algebraic_notation_(chess)#:~:text=Algebraic%20notation%20(or%20AN)%20is,books%2C%20magazines%2C%20and%20newspapers.).
* All movements.
* Movement stack list.
* [Incomplete chess rules](https://en.wikipedia.org/wiki/Rules_of_chess)
* Rules only for pawns.
* Death notes only for pawns.
# How to play
## Starting the pieces
for start the pieces in their initial positions on the board type:
*start*
in normal mode.
## Moviment mode
for make a move type:
*mov*
int normal mode. Once entering in moviment mode you remain in movement mode type:
*back*
to exit and back to the normal mode.
for make a move you first type the name of the piece and the algebraic notation.
Exemple:
*P1w a5*
and type enter.
<p>P1w<space>a5<enter></p>
Attention!  
The name of the piece must be typed as shown on the board and the algebraic notation must always be in lowercase. 
## Pieces and Chessboard
  
## Commands
1. *start* start the game create pieces on the board.
2. *mov* motion mode moving pieces.
2.1. *back* back to normal mode.
3. *output* print the movement stack list.
## Modes
* *:* Normal mode.
* *mov:* Moviment mode.
