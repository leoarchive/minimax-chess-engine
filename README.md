# Command line chess in C
Command line chess game written in C for Windows
  | ♜ | ♞ | ♝ | ♛ | ♚ | ♝ | ♞ | ♜ |
  |----|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
  | ♟ | ♟ | ♟ | ♟ | ♟ | ♟ | ♟ | ♟ |
  | 3a | 3b | 3c | 3d | 3e | 3f | 3g | 3h |
  | 4a | 4b | 4c | 4d | 4e | 4f | 4g | 4h |
  | 5a | 5b | 5c | 5d | 5e | 5f | 5g | 5h |
  | 6a | 6b | 6c | 6d | 6e | 6f | 6g | 6h |
 | ♙ | ♙ | ♙ | ♙ | ♙ | ♙ | ♙ | ♙ |
  | ♖ | ♘ | ♗ | ♔ | ♕ | ♗ | ♘ | ♖ |
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
>for start the pieces in their initial positions on the board type:
>
*start*
>in normal mode.
## Moviment mode
> for make a move type:
> 
*mov*

> int normal mode. Once entering in moviment mode you remain in movement mode type:
> 
*back*
>to exit and back to the normal mode.
for make a move you first type the name of the piece and the algebraic notation.
Exemple:

*P1w a5*
>and type enter.
>
P1w<space\>a5<enter\>
>Attention!  
The name of the piece must be typed as shown on the board and the algebraic notation must always be in lowercase. 
## Pieces and Chessboard
> *Black pieces*
> 
  | ♜ | ♞ | ♝ | ♛ | ♚ | ♝ | ♞ | ♜ |
  |----|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
  | ♟ | ♟ | ♟ | ♟ | ♟ | ♟ | ♟ | ♟ |
  | T1b | C1b | B1b | R1b | D1b | B2b | C2b | T2b |
 | P1b | P2b | P3b | P4b | P5b | P6b | P7b | P8b |
 > *White pieces*
 > 
  | ♙ | ♙ | ♙ | ♙ | ♙ | ♙ | ♙ | ♙ |
  |----|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
  | ♖ | ♘ | ♗ | ♔ | ♕ | ♗ | ♘ | ♖ |
  | P1w | P2w | P3w | P4w | P5w | P6w | P7w | P8w |
  | T1w | C1w | B1w | R1w | D1b | B2b | C2b | T2w |
  > *Chessboard*
  >
  | 1a | 1b | 1c | 1d | 1e | 1f | 1g | 1h | 
  |----|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
  | 2a | 2b | 2c | 2d | 2e | 2f | 2g | 2h |
  | 3a | 3b | 3c | 3d | 3e | 3f | 3g | 3h |
  | 4a | 4b | 4c | 4d | 4e | 4f | 4g | 4h |
  | 5a | 5b | 5c | 5d | 5e | 5f | 5g | 5h |
  | 6a | 6b | 6c | 6d | 6e | 6f | 6g | 6h |
  | 7a | 7b | 7c | 7d | 7e | 7f | 7g | 7h |
  | 8a | 8b | 8c | 8d | 8e | 8f | 8g | 8h |
## Commands
1. *start* start the game create pieces on the board.
2. *mov* motion mode moving pieces.
2.1. *back* back to normal mode.
3. *output* print the movement stack list.
## Modes
* *:* Normal mode.
* *mov:* Moviment mode.
