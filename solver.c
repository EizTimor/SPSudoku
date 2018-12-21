/*
 * solver.c
 *
 *  Created on: Dec 18, 2018
 *      Author: Timor Eizenman & Ido Lerer
 */


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mainAux.h"

#define DEFAULT 0
#define BLOCK 3
#define BOARD 9

int is_finished(Cell **board) {
	int i = 0, j = 0;
	for (; i < BOARD; i++)
		for (j = 0; j < BOARD; j++)
			if (board[i][j].value == DEFAULT)
				return 0;
	return 1;
}

int is_value_valid(Cell **board, int row, int col, int value) {
	int i = 0, j = 0;
	int rows_to_add = 0, cols_to_add = 0;

	for (; i < row * col; i++) {
		if (board[row][i].value == value)
			return 0;
		if (board[i][col].value == value)
			return 0;
	}

	rows_to_add = (row / BLOCK) * BLOCK;
	cols_to_add = (col / BLOCK) * BLOCK;

	for (i = rows_to_add; i < rows_to_add + BLOCK; i++)
		for (j = cols_to_add; j < cols_to_add + BLOCK; j++)
			if (board[i][j].value == value)
				return 0;

	return 1;
}

int deterministic_backtrack(Cell **board) {
	int value = 1;
	int row = 0, col = 0;

	if (is_finished(board) == 1)
		return 1;

	for (; row < BOARD; row++) {
		for (col = 0; col < BOARD; col++) {
			if (board[row][col].value == DEFAULT && board[row][col].isFixed == 0) {
				for (value = 1; value <= BOARD; value++) {
					if (is_value_valid(board, row, col, value)) {
						board[row][col].value = value;
						if (deterministic_backtrack(board))
							return 1;
					}
				}
				board[row][col].value = DEFAULT;
				return 0;
			}
		}
	}
	return 1;
}

void find_options(Cell **board, int row, int col) {
	int value = 0;

	for (; value < BOARD; value++)
		if (is_value_valid(board, row, col, value))
			insert_option(board[row][col], value);
}

int randomized_backtrack(Cell **board) {
	int value, index, count;
	int row = 0, col = 0, i = 0;

	if (is_finished(board) == 1)
		return 1;

	for (; row < BOARD; row++) {
		for (col = 0; col < BOARD; col++) {
			if (board[row][col].value == DEFAULT && board[row][col].isFixed == 0) {
				find_options(board, row, col);
				count = board[row][col].countOptions;
				if (count == 1)
					index = 0;

				for (; i <= count; i++) {
					index = rand() % board[row][col].countOptions;
					value = board[row][col].options[index];
					board[row][col].value = value;
					if (randomized_backtrack(board))
						return 1;

					board[row][col].countOptions--;
					remove_option(board[row][col], index);
				}

				board[row][col].value = DEFAULT;
				return 0;
			}
		}
	}
	return 1;
}


