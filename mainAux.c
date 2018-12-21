/*
 * mainAux.c
 *
 *  Created on: Dec 18, 2018
 *      Author: Timor Eizenman & Ido Lerer
 */

#include <stdio.h>
#include <stdlib.h>
#include "mainAux.h"

#define DEFAULT 0
#define BLOCK 3
#define BOARD 9

int something() {

	return 0;
}

int insert_option(Cell cell, int value) {
	int index = 0;

	for (; index < BOARD; index++)
		if (cell.options[index] == DEFAULT) {
			cell.options[index] = value;
			break;
		}
	cell.countOptions++;

	return 1;
}

int remove_option(Cell cell, int index) {
	for (; index < BOARD - 1; index++)
		cell.options[index] = cell.options[index + 1];
	cell.options[BOARD - 1] = 0;

	return 0;
}

