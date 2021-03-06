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

#ifndef __GAME_H__
#define __GAME_H__


#define BOARD_NUMBER_OF_SQUARES    9

typedef enum Level_t  {INVALID, EASY, MEDIUM, HARD} Level;
typedef enum Marker_t {O = 1, X = -1, EMPTY = 0} Marker;
typedef enum Status_t {UNKNOWN, HUMAN_WON, AI_WON, TIE} Status;

void init_board(int* board);
int is_valid_level(const Level level);
int move(int* board, const int position, const Marker marker);
int is_game_over(const int* board, Status* status);

#endif /* __GAME_H__ */
