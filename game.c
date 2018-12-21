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
