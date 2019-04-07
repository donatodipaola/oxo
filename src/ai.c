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

#define EMPTY_SCORE     0
#define AI_SCORE        1
#define HUMAN_SCORE     -1

int get_other_player_score(int player_score)
{
    if(player_score == HUMAN_SCORE)
    {
        return AI_SCORE;
    }
    else
    {
        return HUMAN_SCORE;
    }
}

void convert_board(const int* board, int* score_board)
{
    for(int i = 0; i < BOARD_NUMEBER_OF_SQUARES; ++i)
    {
        if(board[i] == O) score_board[i] = AI_SCORE;
        if(board[i] == X) score_board[i] = HUMAN_SCORE;
        if(board[i] == EMPTY) score_board[i] = EMPTY_SCORE;
    }
}

int minimax(int* board, int player_score) {
    Status status = UNKNOWN;
    if (is_game_over(board, &status))
    {
        if(status == AI_WON) return HUMAN_SCORE*player_score;
        if(status == HUMAN_WON) return AI_SCORE*player_score;
    }

    int move = -1;
    int score = -2;

    for(int i = 0; i < BOARD_NUMEBER_OF_SQUARES; ++i)
    {
        if(board[i] == EMPTY_SCORE)
        {
            board[i] = player_score;
            int move_score = -minimax(board, get_other_player_score(player_score));
            if(move_score > score)
            {
                score = move_score;
                move = i;
            }
        }
    }
    if(move == -1)
        return 0;
    return score;
}

int ai_move(const int* board)
{
    int move = -1;
    int score = -2;
    int score_board[BOARD_NUMEBER_OF_SQUARES];
    convert_board(board, score_board);

    for(int i = 0; i < BOARD_NUMEBER_OF_SQUARES; ++i)
    {
        if(score_board[i] == EMPTY_SCORE)
        {
            score_board[i] = AI_SCORE;
            int tempScore = -minimax(score_board, HUMAN_SCORE);
            if(tempScore > score)
            {
                score = tempScore;
                move = i;
            }
        }
    }
    return move;
}
