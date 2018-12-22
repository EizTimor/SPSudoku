/*
 * game.c
 *
 *  Created on: Dec 18, 2018
 *      Author: Timor Eizenman & Ido Lerer
 */

#include <stdio.h>
#include <stdlib.h>
#include "game.h"

#define DEFAULT 0

int insert_option(Cell cell, int value, int board_size) {
	int index = 0;

	for (; index < board_size; index++)
		if (cell.options[index] == DEFAULT) {
			cell.options[index] = value;
			break;
		}
	cell.countOptions++;

	return 1;
}

int remove_option(Cell cell, int index, int board_size) {
	for (; index < board_size - 1; index++)
		cell.options[index] = cell.options[index + 1];
	cell.options[board_size - 1] = 0;
	cell.countOptions--;

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

void printCell(Cell cell){
	if (cell.isFixed){
		printf(" .%d", cell.value);
	} else {
		printf("  %d", cell.value);
	}
}

void printRow(Board board, int index) {
	int j = 0, i;
	printf("|");
	while(j < board.board_size){
		for (i = 0; i < board.block_col; i++){
			printCell(board.current[index][j]);
			j++;
		}
		printf(" |");
	}
	printf("\n");
}

void printBoard(Board board) {
	int index = 0, j;
	int rowLength = board.block_row * (3 * board.block_col + 2) + 2;
	printSeparatorRow(rowLength);
	while (index < board.board_size) {
		for (j = 0; j < board.block_row; j++){
			printRow(board, index);
			index++;
		}
		printSeparatorRow(rowLength);
	}
	printf("\n");
}

