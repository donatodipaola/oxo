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

 #include <stdio.h>

#include <gui.h>
#include <game.h>

void play()
{
    int board[BOARD_NUMEBER_OF_SQUARES];
    init_board(board);

    Marker turn_marker = O;
    Status status = UNKNOWN;
    do {
        clean_screen();
        display_game_screen(board, turn_marker);

        if( move(board, get_move(), turn_marker) )
            turn_marker = turn_marker == O ? X : O;

  } while (! is_game_over(board, &status));
  clean_screen();
  display_result_screen(board, status);
}

int main()
{
    display_menu_screen();

    int menu_choice;
    menu_choice = get_menu_choice();
    if(menu_choice == 1)
        play();

    return 0;
}
