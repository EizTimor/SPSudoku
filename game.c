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

void printCell(Cell *cell){
	if (cell->isFixed){
		printf(" .%d", cell->value);
	} else {
		printf("  %d", cell->value);
	}
}

void printRow(Board *board, int index) {
	int j = 0, i;
	printf("|");
	while(j < board->board_size){
		for (i = 0; i < board->block_col; i++){
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
		for (j = 0; j < board->block_row; j++){
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
		if (board->current[row][col].isFixed == 0) {
			board->current[row][col].isFixed = 1;
			amount--;
		}
	}
}
void executeCommand(Command* cmd){

}

Board* create_board(int rows, int cols, int fixed) {
	int i;
	Board* board = (Board*) malloc(sizeof(Board));
	Cell **b = (Cell **) malloc(sizeof(Cell *) * board->board_size);

	board->block_row = rows;
	board->block_col = cols;
	board->board_size = rows * cols;
	board->complete = b;

	for (i = 0; i < board->board_size; i++) {
		b[i] = (Cell *) malloc(sizeof(Cell) * board->board_size);
	}

	fix_cells(board, fixed);
	randomized_backtrack(board);

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
	free(cell);
	return;
}

void destroy_board(Board* board) {
	if (!board)
		return;
	free(board);
	return;
}

int start_game(Board* board) {
	int is_done = 0;
	char in[MAX_COMMAND];
	Command* current;
	while (!is_done) {
		while (current == NULL) {
			if (fgets(in, MAX_COMMAND, stdin) == NULL) {
				/* Here we need to free all memory and exit game */
				return 0;
			}
			current = parseCommand(in);
			if (!current) printf("%s", INV_COMMAND);
		}
		executeCommand(current);
		is_done = is_finished(board);
	}
	return 1;
}
