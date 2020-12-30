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
<p>for start the pieces in their initial positions on the board type:<br /> 
<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;*start*<br /> 
in normal mode.
## Moviment mode
<p>for make a move type:<br />
<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;*mov*<br /> 
<p>int normal mode. Once entering in moviment mode you remain in movement mode type:<br /> 
<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;*back*<br /> 
<p>to exit and back to the normal mode.<br /> 
<p>for make a move you first type the name of the piece and the algebraic notation.<br /> 
<p>Exemple:<br /> 
<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;*P1w a5*<br />  
<p>and type enter.<br />  
<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;P1w<space>a5<enter><br /> 
<p>Attention!<br />  
<p>The name of the piece must be typed as shown on the board and the algebraic notation must always be in lowercase.<br />  
## Pieces and Chessboard
  
## Commands
1. *start* start the game create pieces on the board.
2. *mov* motion mode moving pieces.<\n>  
2.1. *back* back to normal mode.
3. *output* print the movement stack list.
## Modes
* *:* Normal mode.
* *mov:* Moviment mode.
