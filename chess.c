/*
 *  Minimax Chess Engine Algorithm
 *  Copyright (c) 2020 Leonardo Zamboni
 *
 *  this program is free software: you can redistribute it and/or modify
 *  it under the terms of the gnu general public license as published by
 *  the free software foundation, either version 3 of the license, or
 *  (at your option) any later version.
 *
 *  this program is distributed in the hope that it will be useful,
 *  but without any warranty; without even the implied warranty of
 *  merchantability or fitness for a particular purpose.  see the
 *  gnu general public license for more details.
 *
 *  you should have received a copy of the gnu general public license
 *  along with this program.  if not, see <http://www.gnu.org/licenses/>.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "chess.h"

char *AN[]
    = { "a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8", "a7", "b7", "c7",
        "d7", "e7", "f7", "g7", "h7", "a6", "b6", "c6", "d6", "e6", "f6",
        "g6", "h6", "a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5", "a4",
        "b4", "c4", "d4", "e4", "f4", "g4", "h4", "a3", "b3", "c3", "d3",
        "e3", "f3", "g3", "h3", "a2", "b2", "c2", "d2", "e2", "f2", "g2",
        "h2", "a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1" };

char *PIECES[] = { " ", "♜", "♞", "♝", "♛", "♚", "♝", "♞", "♜", "♟", "♟",
                   "♟", "♟", "♟", "♟", "♟", "♟", "♙", "♙", "♙", "♙", "♙",
                   "♙", "♙", "♙", "♖", "♘", "♗", "♕", "♔", "♗", "♘", "♖" };

int board[]
    = { 1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15, 16,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32 };

color player = white;

int white_captures_counter = 0;
int black_captures_counter = 0;
int white_captures[32];
int black_captures[32];

int from_value;
int to_value;
int from_position;
int to_position;
char from_char;
char to_char;

int aux_board[64];
int bitboard[64];

void
print_chessboard_and_pieces (size_t s, int n, bool p)
{
  if (s == 64)
    {
      char l = 'a';
      printf ("\n  ");
      while (l != 'i')
        printf ("%c ", l++);
      return;
    }
  else if (!s)
    printf ("%d ", n--);
  else if (!(s % 8))
    printf ("\n%d ", n--);
  else
    p = !p;
  printf ("%s%s%s " DEFAULT, p ? BLACK_BACKGROUND : WHITE_BACKGROUND,
          board[s] < WHITE_PIECES_VALUE_MIN ? BLACK_PIECE : WHITE_PIECE,
          PIECES[board[s]]);
  print_chessboard_and_pieces (++s, n, p);
}

int
set_move (void)
{
  char *from = (char *)malloc (2 * sizeof (char));
  char *to = (char *)malloc (2 * sizeof (char));
  print_capture_pieces ();
  printf ("%s: ", player ? "white" : "black");
  scanf (" %s %s", from, to);
  if (!strcmp (from, "e"))
    return 2;
  int from_position_move = get_position_from_char (from);
  int to_position_move = get_position_from_char (to);
  if (is_checkmate (from_position_move, to_position_move))
    {
      printf ("invalid move");
      return 1;
    }
  set_bitboard (from);
  if (!bitboard[to_position_move])
    {
      printf ("invalid move");
      return 1;
    }
  else if (board[to_position_move])
    {
      if (player)
        white_captures[white_captures_counter++] = board[to_position_move];
      else
        black_captures[black_captures_counter++] = board[to_position_move];
    }
  board[to_position_move] = board[from_position_move];
  board[from_position_move] = 0;
  SWAP_PLAYER_TURN
  return 0;
}

int
is_checkmate (int f, int t)
{
  int king_value;
  int king_position;
  int min_pieces_value;
  int max_pieces_value;
  bool INVALID_MOVE;
  if (player)
    {
      min_pieces_value = BLACK_PIECES_VALUE_MIN;
      max_pieces_value = BLACK_PIECES_VALUE_MAX;
      king_value = WHITE_KING_VALUE;
    }
  else
    {
      min_pieces_value = WHITE_PIECES_VALUE_MIN;
      max_pieces_value = WHITE_PIECES_VALUE_MAX;
      king_value = BLACK_KING_VALUE;
    }
  SWAP_PLAYER_TURN
  set_aux_board ();
  board[t] = board[f];
  board[f] = 0;
  king_position = get_position_from_value (king_value);
  for (size_t i = min_pieces_value; i < max_pieces_value; ++i)
    {
      set_bitboard (AN[get_position_from_value (i)]);
      if (bitboard[king_position])
        {
          INVALID_MOVE = true;
          break;
        }
    }
  get_aux_board ();
  SWAP_PLAYER_TURN
  if (INVALID_MOVE)
    return 1;
  else
    return 0;
}

int
get_rules (char *f, char *t)
{
  if (!strcmp (f, t))
    return 0;
  from_char = f[0];
  to_char = t[0];
  from_value = f[1] - '0';
  to_value = t[1] - '0';
  from_position = board[get_position_from_char (f)];
  to_position = board[get_position_from_char (t)];
  if (!from_position)
    return 0;
  if (player)
    {
      if (from_position < WHITE_PIECES_VALUE_MIN
          || to_position > BLACK_PIECES_VALUE_MAX)
        return 0;
    }
  else
    {
      if (from_position > BLACK_PIECES_VALUE_MAX
          || to_position && to_position < WHITE_PIECES_VALUE_MIN)
        return 0;
    }
  if (from_position > 16 && from_position < 25
      || from_position > 8 && from_position < 17)
    return pawn ();
  else if (from_position == 27 || from_position == 30 || from_position == 3
           || from_position == 6)
    return bishop (f, t);
  else if (from_position == 26 || from_position == 31 || from_position == 2
           || from_position == 7)
    return knight ();
  else if (from_position == 25 || from_position == 32 || from_position == 1
           || from_position == 8)
    return rook (f, t);
  else if (from_position == 28 || from_position == 4)
    return queen (f, t);
  else if (from_position == 29 || from_position == 5)
    return king ();
  return 1;
}

int
get_position_from_value (int p)
{
  for (int i = 0; i < 64; ++i)
    if (board[i] == p)
      return i;
  return 0;
}

int
get_position_from_char (char *p)
{
  for (int i = 0; i < 64; ++i)
    if (!strcmp (AN[i], p))
      return i;
  return 0;
}

int
pawn (void)
{
  bool two_square = false;
  if (player)
    {
      if (from_value == 2)
        two_square = true;
      if (to_position && to_position < 17 && to_char == from_char
          || to_value < from_value)
        return 0;
    }
  else
    {
      if (from_value == 7)
        two_square = true;
      if (to_position > 16 && to_char == from_char || to_value > from_value)
        return 0;
    }
  if (two_square)
    {
      if (player)
        {
          if (to_value != 3 && to_value != 4)
            return 0;
        }
      else
        {
          if (to_value != 6 && to_value != 5)
            return 0;
        }
    }
  else
    {
      if (player)
        {
          if (to_value > (from_value + 1))
            return 0;
        }
      else
        {
          if (to_value < (from_value - 1))
            return 0;
        }
    }
  if (to_char != from_char)
    {
      if (to_char != (from_char + 1) && to_char != (from_char - 1)
          || from_value == to_value)
        return 0;
      if (player)
        {
          if (to_position > 16 || to_value > (from_value + 1))
            return 0;
        }
      else
        {
          if (to_position && to_position < 17 || to_value < (from_value - 1))
            return 0;
        }
      if (!to_position)
        return 0;
    }
  return 1;
}

int
bishop (char *f, char *t)
{
  int v = get_validation (f, t, false);
  if (to_char == from_char || v == 1 || v && v != get_position_from_char (t))
    return 0;
  int c = 0;
  char l;
  if (to_char > from_char)
    {
      l = from_char;
      while (l++ != to_char)
        c++;
    }
  else
    {
      l = from_char;
      while (l-- != to_char)
        c++;
    }
  if (to_value == (from_value + c) || to_value == (from_value - c))
    return 1;
  return 0;
}

int
knight (void)
{
  if (to_value == (from_value + 2) && to_char == (from_char + 1)
      || to_value == (from_value + 2) && to_char == (from_char - 1)
      || to_value == (from_value - 2) && to_char == (from_char - 1)
      || to_value == (from_value - 2) && to_char == (from_char + 1)
      || to_char == (from_char + 2) && to_value == (from_value + 1)
      || to_char == (from_char + 2) && to_value == (from_value - 1)
      || to_char == (from_char - 2) && to_value == (from_value - 1)
      || to_char == (from_char - 2) && to_value == (from_value + 1))
    return 1;
  return 0;
}

int
rook (char *f, char *t)
{
  int v = get_validation (f, t, true);
  if (to_value != from_value && to_char != from_char || v == 1
      || v && v != get_position_from_char (t))
    return 0;
  return 1;
}

int
queen (char *f, char *t)
{
  if (!rook (f, t) && !bishop (f, t))
    return 0;
  return 1;
}

int
king (void)
{
  if (to_value == (from_value + 1) && to_char == (from_char + 1)
      || to_value == (from_value + 1) && to_char == (from_char - 1)
      || to_value == (from_value - 1) && to_char == (from_char - 1)
      || to_value == (from_value - 1) && to_char == (from_char + 1)
      || to_value == from_value && to_char == (from_char + 1)
      || to_value == from_value && to_char == (from_char - 1)
      || to_value == (from_value + 1) && to_char == from_char
      || to_value == (from_value - 1) && to_char == from_char)
    return 1;
  return 0;
}

void
get_aux_board (void)
{
  for (size_t i = 0; i < 64; ++i)
    board[i] = aux_board[i];
}

void
set_aux_board (void)
{
  for (size_t i = 0; i < 64; ++i)
    aux_board[i] = board[i];
}

void
print_capture_pieces (void)
{
  if (player)
    {
      for (int i = 0; i < white_captures_counter; ++i)
        printf ("%s ", PIECES[white_captures[i]]);
    }
  else
    {
      for (int i = 0; i < black_captures_counter; ++i)
        printf ("%s ", PIECES[black_captures[i]]);
    }
  if (player && white_captures_counter || !player && black_captures_counter)
    puts ("");
}

void
set_bitboard (char *f)
{
  for (size_t i = 0; i < 64; ++i)
    {
      if (get_rules (f, AN[i]) == 1)
        bitboard[i] = 1;
      else
        bitboard[i] = 0;
    }
}

void
print_bitboard (void)
{
  for (size_t i = 0; i < 64; ++i)
    {
      if (i % 8 == 0)
        puts ("");
      printf ("%d ", bitboard[i]);
    }
  puts ("");
}

int
_set_validation (char *v[], int f, int t)
{
  int k;
  if (f > t)
    {
      for (int j = f - 1; j > t; --j)
        {
          for (k = 0; k < 64; ++k)
            if (!strcmp (AN[k], v[j]))
              break;
          if (player)
            {
              if (board[k] > BLACK_PIECES_VALUE_MAX)
                return 1;
              else if (board[k] && board[k] < WHITE_PIECES_VALUE_MIN)
                return k;
            }
          if (!player)
            {
              if (board[k] && board[k] < WHITE_PIECES_VALUE_MIN)
                return 1;
              else if (board[k] > BLACK_PIECES_VALUE_MAX)
                return k;
            }
        }
    }
  else
    {
      for (int j = f + 1; j < t; ++j)
        {
          for (k = 0; k < 64; ++k)
            if (!strcmp (AN[k], v[j]))
              break;
          if (!player)
            {
              if (board[k] > BLACK_PIECES_VALUE_MAX)
                return 1;
              else if (board[k] && board[k] < WHITE_PIECES_VALUE_MIN)
                return k;
            }
          if (player)
            {
              if (board[k] && board[k] < WHITE_PIECES_VALUE_MIN)
                return 1;
              else if (board[k] > BLACK_PIECES_VALUE_MAX)
                return k;
            }
        }
    }
  return 0;
}

int
get_validation (char *f, char *t, bool r)
{
  char *AN_DIAGONAL[] = {
    "a8", "b8", "a7", "c8", "b7", "a6", "d8", "c7", "b6", "a5", "e8", "d7",
    "c6", "b5", "a4", "f8", "e7", "d6", "c5", "b4", "a3", "g8", "f7", "e6",
    "d5", "c4", "b3", "a2", "h8", "g7", "f6", "e5", "d4", "c3", "b2", "a1",
    "h7", "g6", "f5", "e4", "d3", "c2", "b1", "h6", "g5", "f4", "e3", "d2",
    "c1", "h5", "g4", "f3", "e2", "d1", "h4", "g3", "f2", "e1", "h3", "g2",
    "f1", "h2", "g1", "h1", "h8", "g8", "h7", "f8", "g7", "h6", "e8", "f7",
    "g6", "h5", "d8", "e7", "f6", "g5", "h4", "c8", "d7", "e6", "f5", "g4",
    "h3", "b8", "c7", "d6", "e5", "f4", "g3", "h2", "a8", "b7", "c6", "d5",
    "e4", "f3", "g2", "h1", "a7", "b6", "c5", "d4", "e3", "f2", "g1", "a6",
    "b5", "c4", "d3", "e2", "f1", "a5", "b4", "c3", "d2", "e1", "a4", "b3",
    "c2", "d1", "a3", "b2", "c1", "a2", "b1", "a1",
  };
  char *AN_VERTICAL_AND_HORIZONTAL[] = {
    "a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8", "a7", "b7", "c7", "d7",
    "e7", "f7", "g7", "h7", "a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6",
    "a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5", "a4", "b4", "c4", "d4",
    "e4", "f4", "g4", "h4", "a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3",
    "a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2", "a1", "b1", "c1", "d1",
    "e1", "f1", "g1", "h1", "a8", "a7", "a6", "a5", "a4", "a3", "a2", "a1",
    "b8", "b7", "b6", "b5", "b4", "b3", "b2", "b1", "c8", "c7", "c6", "c5",
    "c4", "c3", "c2", "c1", "d8", "d7", "d6", "d5", "d4", "d3", "d2", "d1",
    "e8", "e7", "e6", "e5", "e4", "e3", "e2", "e1", "f8", "f7", "f6", "f5",
    "f4", "f3", "f2", "f1", "g8", "g7", "g6", "g5", "g4", "g3", "g2", "g1",
    "h8", "h7", "h6", "h5", "h4", "h3", "h2", "h1",
  };
  if (r)
    {
      for (int i = 0; i < 128; ++i)
        {
          if (!strcmp (AN_VERTICAL_AND_HORIZONTAL[i], f))
            {
              for (int j = 0; j < 128; ++j)
                {
                  if (!strcmp (AN_VERTICAL_AND_HORIZONTAL[j], t))
                    {
                      if ((j - i) < -8 || (j - i) > 8)
                        continue;
                      else
                        return _set_validation (AN_VERTICAL_AND_HORIZONTAL, i,
                                                j);
                    }
                }
            }
        }
    }
  else
    {
      for (int i = 0; i < 128; ++i)
        {
          if (!strcmp (AN_DIAGONAL[i], f))
            {
              for (int j = 0; j < 128; ++j)
                {
                  if (!strcmp (AN_DIAGONAL[j], t))
                    {
                      if ((j - i) < -8 || (j - i) > 8)
                        continue;
                      else
                        return _set_validation (AN_DIAGONAL, i, j);
                    }
                }
            }
        }
    }
  return 0;
}
