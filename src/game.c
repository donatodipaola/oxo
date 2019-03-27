/*
 * Copyright (C) 2019 Donato Di Paola
 *
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <game.h>


int _is_position_valid(const int position)
{
    if( position >= 0 && position < BOARD_NUMEBER_OF_SQUARES )
    {
        return 1;
    }
    return 0;
}

int _is_position_empty(const int* board, const int position)
{
    if( board[position] == EMPTY )
    {
        return 1;
    }
    return 0;
}

int _are_no_more_moves(const int* board)
{
  for (int i=0; i < BOARD_NUMEBER_OF_SQUARES; ++i) {
      if ( board[i] == EMPTY )
          return 0;
  }
  return 1;
}

int _has_player_won(const int* board, const Marker marker)
{
    if
    (
        (board[0] == marker && board[1] == marker && board[2] == marker) ||
        (board[3] == marker && board[4] == marker && board[5] == marker) ||
        (board[6] == marker && board[7] == marker && board[8] == marker) ||

        (board[0] == marker && board[3] == marker && board[6] == marker) ||
        (board[1] == marker && board[4] == marker && board[7] == marker) ||
        (board[2] == marker && board[5] == marker && board[8] == marker) ||

        (board[0] == marker && board[4] == marker && board[8] == marker) ||
        (board[2] == marker && board[4] == marker && board[6] == marker)
    )
        return 1;
    return 0;
}


void init_board(int* board)
{
    for (int i=0; i < BOARD_NUMEBER_OF_SQUARES; ++i) {
        board[i] = EMPTY;
    }
}

int move(int* board, const int position, Marker marker)
{
    if( _is_position_valid(position) &&
        _is_position_empty(board, position) )
    {
        board[position] = marker;
        return 1;
    }
    return 0;
}

int is_game_over(const int* board, Status* status)
{
  if( _has_player_won(board,O) )
  {
    *status = O_WON;
    return 1;
  }
  if( _has_player_won(board,X) )
  {
    *status = X_WON;
    return 1;
  }
  if( _are_no_more_moves(board) )
  {
    *status = TIE;
    return 1;
  }
  return 0;
}
