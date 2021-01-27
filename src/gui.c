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

char _get_marker_char(Marker maker)
{
    if(maker == O)    return 'O';
    if(maker == X)    return 'X';
    return '.';
}

char _get_marker_by_coordinates(const int* board, int x, int y)
{
  return board[x+BOARD_SIDE_DIMENSION*y];
}

void _display_game_title(Marker marker) {
    printf("   OXO    |  Player [%c] turn \n", _get_marker_char(marker));
}

void _display_result_title() {
    printf("   OXO    |  Game Over \n");
}

void _display_board(int* board) {
    unsigned int offset[] = {0,3,6};
    for (unsigned int i=0; i < 3; ++i) {
        printf(" %u  %u  %u  | ", offset[i]+1, offset[i]+2, offset[i]+3);
        for (unsigned int j=0; j < 3; ++j) {
            printf(" %c ", _get_marker_char(_get_marker_by_coordinates(board,j,i)) );
        }
        printf("\n");
    }
}

void _display_choice_message(){
    printf("          |  Choice :");
}

void _display_move_message(){
    printf("          |  Player's move :");
}

void _display_result_message(Status status)
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


void clean_screen() {
    printf(CURSOR_UP);
    for (unsigned int i=0; i < SCREEN_HEIGHT - 1; ++i) {
        printf(ERASE_LINE);
        printf(CURSOR_UP);
    }
}

void display_game_screen(int* board, Marker marker) {
    printf("\n");
    _display_game_title(marker);
    printf("\n");
    _display_board(board);
    printf("\n");
    _display_move_message();
}

void display_result_screen(int* board, Status status)
{
    printf("\n");
    _display_result_title();
    printf("\n");
    _display_board(board);
    printf("\n");
    _display_result_message(status);
}

int chartoi(const char character)
{
    return character - '0';
}

int get_move()
{
    char move[20]; 
    scanf("%[^\n]%*c", move);
    if( (strlen(move) == 1) && isdigit(move[0]) )
    {
        // conversion to internal board value range (0-8) from user input (1-9)
        return chartoi(move[0]) - 1;
    }
    return -1;
}
