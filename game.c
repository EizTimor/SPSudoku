/*
 * game.c
 *
 *  Created on: Dec 18, 2018
 *      Author: Timor Eizenman & Ido Lerer
 */

#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "solver.h"
#include "parser.h"

#define DEFAULT 0
#define MAX_COMMAND 1024
#define INV_COMMAND "Error: invalid command/n"
#define EXIT_MSG "Exiting...\n"
#define SUCCESS_MSG "Puzzle solved successfully"
#define VALIDATION_PASSED "Validation passed: board is solvable"
#define VALIDATION_FAILED "Validation failed: board is unsolvable\n"

enum commandID {
	SET, HINT, VALIDATE, RESTART, EXIT
};

int insert_option(Cell* cell, int value, int board_size) {
	int index = 0;

	for (; index < board_size; index++)
		if (cell->options[index] == DEFAULT) {
			cell->options[index] = value;
			break;
		}
	cell->countOptions++;

	return 1;
}

int remove_option(Cell* cell, int index, int board_size) {
	for (; index < board_size - 1; index++)
		cell->options[index] = cell->options[index + 1];
	cell->options[board_size - 1] = 0;
	cell->countOptions--;

	return 0;
}

void printSeparatorRow(int rowLength) {
	int i;
	char *line = (char*) malloc(rowLength * sizeof(char));
	for (i = 0; i < rowLength - 1; i++) {
		line[i] = '-';
	}
	line[rowLength - 1] = '\0';
	printf("%s\n", line);
	free(line);
}

void printCell(Cell *cell) {
	if (cell->isFixed) {
		printf(" .%d", cell->value);
	} else {
		printf("  %d", cell->value);
	}
}

void printRow(Board *board, int index) {
	int j = 0, i;
	printf("|");
	while (j < board->board_size) {
		for (i = 0; i < board->block_col; i++) {
			printCell(&board->current[index][j]);
			j++;
		}
		printf(" |");
	}
	printf("\n");
}

void printBoard(Board* board) {
	int index = 0, j;
	int rowLength = board->block_row * (3 * board->block_col + 2) + 2;
	printSeparatorRow(rowLength);
	while (index < board->board_size) {
		for (j = 0; j < board->block_row; j++) {
			printRow(board, index);
			index++;
		}
		printSeparatorRow(rowLength);
	}
	printf("\n");
}

void fix_cells(Board* board, int amount) {
	int row, col;
	while (amount > 0) {
		row = rand() % board->board_size;
		col = rand() % board->board_size;
		if (board->complete[row][col].isFixed == 0) {
			board->complete[row][col].isFixed = 1;
			amount--;
		}
	}
}

void exit_game(Board* board) {
	printf("%s", EXIT_MSG);
	free(board);
}

void clear_solution(Board* board) {
	int i, j;
	for (i = 0; i < board->board_size; i++)
		for (j = 0; j < board->board_size; j++)
			board->complete[i][j] = board->current[i][j];
}

int executeCommand(Command* cmd, Board* board) {
	int x, y, val;
	switch (cmd->id) {
	case SET:
		x = cmd->params[0] - 1;
		y = cmd->params[1] - 1;
		val = cmd->params[2];
		if (board->current[y][x].isFixed) {
			printf("Error: cell is fixed");
			return 0;
		}
		if (!is_value_valid(board, y, x, val)) {
			printf("Error: value is invalid");
			return 0;
		}
		board->current[y][x].value = val;
		printBoard(board);
		return 1;

	case HINT:
		x = cmd->params[0] - 1;
		y = cmd->params[1] - 1;
		printf("Hint: set cell to %d", board->current[y][x].value);
		return 0;

	case VALIDATE:
		clear_solution(board);
		if (deterministic_backtrack(board)) {
			printf("%s", VALIDATION_PASSED);
		} else {
			printf("%s", VALIDATION_FAILED);
		}
		return 0;

	case RESTART:
		free(board);
		return RESTART;

	case EXIT:
		exit_game(board);
		return EXIT;
	}
	return 0;
}

Board* create_board(int rows, int cols, int fixed) {
	int i, j;
	Board* board = (Board*) malloc(sizeof(Board));
	Cell **complete = (Cell **) malloc(sizeof(Cell *) * board->board_size);
	Cell **current = (Cell **) malloc(sizeof(Cell *) * board->board_size);

	board->block_row = rows;
	board->block_col = cols;
	board->board_size = rows * cols;
	board->complete = complete;
	board->current = current;

	for (i = 0; i < board->board_size; i++) {
		complete[i] = (Cell *) malloc(sizeof(Cell) * board->board_size);
		current[i] = (Cell *) malloc(sizeof(Cell) * board->board_size);
	}

	fix_cells(board, fixed);
	randomized_backtrack(board);

	for (i = 0; i < board->board_size; i++)
		for (j = 0; j < board->board_size; j++)
			if (complete[i][j].isFixed) {
				current[i][j].value = complete[i][j].value;
				current[i][j].isFixed = 1;
			}

	return board;
}

Cell* create_cell(int board_size) {
	Cell* cell = (Cell*) malloc(sizeof(Cell));

	cell->countOptions = 0;
	cell->isFixed = 0;
	cell->value = DEFAULT;
	cell->options = (int*) malloc(sizeof(int) * board_size);

	return cell;
}

void destroy_cell(Cell* cell) {
	if (!cell)
		return;
	free(cell->options);
	free(cell);
}

void destroy_board(Board* board) {
	int i, j;
	if (!board)
		return;
	for (i = 0; i < board->board_size; i++) {
		for (j = 0; j < board->board_size; j++) {
			free(&board->complete[i][j]);
			free(&board->current[i][j]);
		}
		free(board->complete[i]);
		free(board->current[i]);
	}
	free(board);
}

int start_game(Board* board) {
	int is_done = 0, to_check = 0;
	char in[MAX_COMMAND];
	Command* current;
	printBoard(board);
	while (!is_done) {
		while (current == NULL) {
			if (fgets(in, MAX_COMMAND, stdin) == NULL) {
				exit_game(board);
				return 0;
			}
			current = parseCommand(in);
			if (!current)
				printf("%s", INV_COMMAND);
		}
		to_check = executeCommand(current, board);
		if (to_check == EXIT) {
			return 0;
		}
		if (to_check == RESTART) {
			return 1;
		}
		if (to_check)
			is_done = is_finished(board);
	}
	printf("%s", SUCCESS_MSG);

	while (1) {
		if (fgets(in, MAX_COMMAND, stdin) == NULL) {
			exit_game(board);
			return 0;
		}
		current = parseCommand(in);
		if (!current || !(current->id == RESTART || current->id == EXIT)){
			printf("%s", INV_COMMAND);
		} else{
			if (current->id == RESTART) return 1;
			if (current->id == EXIT) return 0;
		}
	}
	return 1;
}
