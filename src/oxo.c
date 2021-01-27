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
#include <stdlib.h>
#include <time.h>

#include <gui.h>
#include <game.h>
#include <ai.h>


int main()
{
    int board[BOARD_NUMBER_OF_SQUARES];
    init_board(board);

    Level level = 0;
    do 
    {
        display_menu_screen();
        level = get_level_choice();
        clean_screen();
    } 
    while (! is_valid_level(level));

    Marker turn_marker;
    srand(time(NULL));

    int coin_toss = rand() % 2;
    if (coin_toss == 0)
        turn_marker = HUMAN_MARKER;
    if (coin_toss == 1)
        turn_marker = AI_MARKER;

    Status status = UNKNOWN;

    do 
    {
        display_game_screen(board, turn_marker);

        switch (turn_marker) 
        {
            case HUMAN_MARKER:
                if( move(board, get_move(), HUMAN_MARKER) )
                {
                    turn_marker = AI_MARKER;
                }
                break;
            case AI_MARKER:
                if( move(board, ai_move(board, level), AI_MARKER) )
                {
                    printf("\n");
                    turn_marker = HUMAN_MARKER;
                } 
                else
                {
                    // AI picked an invalid position... something went wrong
                    abort();
                }
                break;
            case EMPTY:
                break;
        }

        clean_screen();
    } 
    while (! is_game_over(board, &status));

    display_result_screen(board, status);

    return 0;
}
