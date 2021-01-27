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

#include <ai.h>
#include <game.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>


typedef enum
{
    HUMAN_ROUND = -1,
    AI_ROUND = 1
} RoundType;

int _minmax(int* local_board, RoundType roundType)
{
    Status local_status;
    if (is_game_over(local_board, &local_status))
    {
        if (local_status == AI_WON)
        {
            return 1;
        }
        else if (local_status == HUMAN_WON)
        {
            return -1;
        }
        else
        {
            return 0;
        }
    }

    int value;

    if (roundType == HUMAN_ROUND)
    {
        value = INT_MAX;
        for (int i = 0; i < BOARD_NUMBER_OF_SQUARES; ++i)
        {
            if (local_board[i] == EMPTY)
            {
                local_board[i] = HUMAN_MARKER;
                const int action_result = _minmax(local_board, AI_ROUND);
                local_board[i] = EMPTY;
                if (action_result < value)
                {
                    value = action_result;
                }
            }
        }
    }
    else
    {
        value = INT_MIN;
        for (int i = 0; i < BOARD_NUMBER_OF_SQUARES; ++i)
        {
            if (local_board[i] == EMPTY)
            {
                local_board[i] = AI_MARKER;
                const int action_result = _minmax(local_board, HUMAN_ROUND);
                local_board[i] = EMPTY;
                if (value < action_result)
                {
                    value = action_result;
                }
            }
        }
    }

    return value;
}

int _minmax_move(const int* board)
{
    int move = -1;
    int score = INT_MIN;

    int local_board[BOARD_NUMBER_OF_SQUARES];
    memcpy(local_board, board, sizeof(local_board));

    for (int i = 0; i < BOARD_NUMBER_OF_SQUARES; ++i)
    {
        if (local_board[i] == EMPTY)
        {
            local_board[i] = AI_MARKER;
            const int action_result = _minmax(local_board, HUMAN_ROUND);
            local_board[i] = EMPTY;
            if (score < action_result)
            {
                score = action_result;
                move = i;
            }
        }
    }

    return move;
}

int _is_valid_move(const int* board, const int move)
{
    if (board[move] == EMPTY)
    {
        return 1;
    }
    return 0;
}

int _random_move(const int* board)
{
    int move = 4;   //center position
    if(_is_valid_move(board, move))
    {
        return move;
    }

    do 
    {
        move = rand() % 9;
    } 
    while (! _is_valid_move(board, move));

    return move;
}

int _partial_min_max(const int* board)
{
    int move = -1;
    move = _minmax_move(board);

    if ((rand() % 3) == 0)
    {
        move = _random_move(board);
    }

    return move;
}

int ai_move(const int* board, const Level level)
{
    int move = -1;
    switch (level) 
    { 
        case EASY:
            move = _random_move(board);
            break;
        case MEDIUM:
            move = _partial_min_max(board);
            break;
        case HARD:
            move = _minmax_move(board);
            break;
        case INVALID:
            break;
    }

    return move;
}
