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

#include <gui.h>

#include <stdio.h>
#include <ctype.h>
#include <string.h>


#define BOARD_SIDE_DIMENSION    3

#define SCREEN_HEIGHT           8

#define CURSOR_UP  "\x1b[A"
#define ERASE_LINE "\33[2K\r"

int _char_to_int(const char character)
{
    return character - '0';
}

int _get_user_input()
{
    char move[20]; 
    scanf("%[^\n]%*c", move);
    if( (strlen(move) == 1) && isdigit(move[0]) )
    {
        return _char_to_int(move[0]);
    }
    return -1;
}
int _convert_to_internal_board_position(const int position)
{
    return (position - 1);
}

char _get_marker_char(Marker maker) 
{
    if(maker == O)    return 'O';
    if(maker == X)    return 'X';
    return '.';
}

char _get_marker_by_coordinates(const int* board, const int x, const int y) 
{
  return board[x+BOARD_SIDE_DIMENSION*y];
}

void _display_menu_title() 
{
    printf("   OXO    |  Game level: \n");
}

void _display_game_title(const Marker marker) 
{
    printf("   OXO    |  Player [%c] turn \n", _get_marker_char(marker));
}

void _display_result_title() 
{
    printf("   OXO    |  Game Over \n");
}

void _display_menu() 
{
    printf(" O  X  O  |  1. Easy\n");
    printf(" X  O  X  |  2. Medium\n");
    printf(" 0  X  O  |  3. Hard\n");
}

void _display_board(const int* board) 
{
    unsigned int offset[] = {0,3,6};
    for (unsigned int i=0; i < 3; ++i) 
    {
        printf(" %u  %u  %u  | ", offset[i]+1, offset[i]+2, offset[i]+3);
        for (unsigned int j=0; j < 3; ++j) 
        {
            printf(" %c ", _get_marker_char(_get_marker_by_coordinates(board,j,i)) );
        }
        printf("\n");
    }
}

void _display_choice_message() 
{
    printf("          |  Choice :");
}

void _display_move_message() 
{
    printf("          |  Player's move :");
}

void _display_result_message(const Status status) 
{
    switch(status)
    {
        case (AI_WON):
        {
            printf("          |  AI won\n");
            break;
        }
        case (HUMAN_WON):
        {
            printf("          |  Player won\n");
            break;
        }
        case (TIE):
        {
            printf("          |  Drawn game\n");
            break;
        }
        case (UNKNOWN):
        {
            break;
        }
    }
}



void clean_screen() 
{
    printf(CURSOR_UP);
    for (unsigned int i=0; i < SCREEN_HEIGHT - 1; ++i) 
    {
        printf(ERASE_LINE);
        printf(CURSOR_UP);
    }
}

void display_menu_screen()
{
    printf("\n");
    _display_menu_title();
    printf("\n");
    _display_menu();
    printf("\n");
    _display_choice_message();
}

void display_game_screen(const int* board, const Marker marker) 
{
    printf("\n");
    _display_game_title(marker);
    printf("\n");
    _display_board(board);
    printf("\n");
    _display_move_message();
}

void display_result_screen(const int* board, const Status status)
{
    printf("\n");
    _display_result_title();
    printf("\n");
    _display_board(board);
    printf("\n");
    _display_result_message(status);
}

Level get_level_choice()
{
    int user_input = _get_user_input();
    Level level = INVALID;
    
    switch (user_input) 
    {
        case 1:
            level = EASY;
            break;
        case 2:
            level = MEDIUM;
            break;
        case 3:
            level = HARD;
            break;
    }

    return level;
}

int get_move()
{
    int position = _get_user_input();
    if( position != -1)
    {
        return _convert_to_internal_board_position(position);
    }
    return position;
}




