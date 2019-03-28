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
#include <string.h>


#define BOARD_SIDE_DIMENSION        3

#define CURSOR_UP  "\x1b[A"
#define ERASE_LINE "\33[2K\r"

char _get_marker_char(Marker maker)
{
    if(maker == O)      return 'O';
    if(maker == X)      return 'X';
    return '.';
}

char _get_marker_by_coordinates(const int* board, int x, int y)
{
  return board[x+BOARD_SIDE_DIMENSION*y];
}

void _display_menu_title() {
    printf("   OXO    |  Main Menu  \n");
}

void _display_game_title(Marker marker) {
    printf("   OXO    |  Player %c's turn \n", _get_marker_char(marker));
}

void _display_result_title() {
    printf("   OXO    |  Game Over \n");
}

void _display_menu() {
    printf(" 1  2  3  |  1. Play \n");
    printf(" 4  5  6  |  2. Quit \n");
    printf(" 7  8  9  |  \n");
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
        case (O_WON):
        {
            printf("          |  Player O won!\n");
            break;
        }
        case (X_WON):
        {
            printf("          |  Player X won!\n");
            break;
        }
        case (TIE):
        {
            printf("          |  Tie!\n");
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
    for (unsigned int i=0; i < 7; ++i) {
        printf(ERASE_LINE);
        printf(CURSOR_UP);
    }
}

void display_menu_screen() {
    printf("\n");
    _display_menu_title();
    printf("\n");
    _display_menu();
    printf("\n");
    _display_choice_message();
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

int get_menu_choice()
{
    int menu_choice;
    scanf("%d", &menu_choice);
    return menu_choice;
}

int get_move()
{
    int move;
    scanf("%d", &move);
    return move - 1;
}
