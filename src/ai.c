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

typedef enum
{
    HUMAN_ROUND = -1,
    AI_ROUND = 1
} RoundType;

int minmax(int* board, RoundType roundType)
{
    Status status;
    if (is_game_over(board, &status))
    {
        if (status == AI_WON)
        {
            return 1;
        }
        else if (status == HUMAN_WON)
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
        for (int i = 0; i < BOARD_NUMEBER_OF_SQUARES; ++i)
        {
            if (board[i] == EMPTY)
            {
                board[i] = HUMAN_MARKER;
                const int action_result = minmax(board, AI_ROUND);
                board[i] = EMPTY;
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
        for (int i = 0; i < BOARD_NUMEBER_OF_SQUARES; ++i)
        {
            if (board[i] == EMPTY)
            {
                board[i] = AI_MARKER;
                const int action_result = minmax(board, HUMAN_ROUND);
                board[i] = EMPTY;
                if (value < action_result)
                {
                    value = action_result;
                }
            }
        }
    }

    return value;
}

int ai_move(int* board)
{
    int move = -1;
    int score = INT_MIN;

    for (int i = 0; i < BOARD_NUMEBER_OF_SQUARES; ++i)
    {
        if (board[i] == EMPTY)
        {
            board[i] = AI_MARKER;
            const int action_result = minmax(board, HUMAN_ROUND);
            board[i] = EMPTY;
            if (score < action_result)
            {
                score = action_result;
                move = i;
            }
        }
    }

    return move;
}
